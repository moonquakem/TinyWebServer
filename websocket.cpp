#include "websocket.h"
#include <sha1.h>
#include <base64.h>
#include <cstring>

bool WebSocketFrame::is_websocket_handshake(const std::string& req) {
    return req.find("Upgrade: websocket") != std::string::npos;
}

std::string WebSocketFrame::make_handshake_response(const std::string& key) {
    std::string accept = key + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    unsigned char sha1[20];
    SHA1(sha1, accept.c_str(), accept.size());
    std::string encoded = base64_encode(sha1, 20);
    return "HTTP/1.1 101 Switching Protocols\r\n"
           "Upgrade: websocket\r\n"
           "Connection: Upgrade\r\n"
           "Sec-WebSocket-Accept: " + encoded + "\r\n\r\n";
}

// 简单文本帧（掩码由客户端发来时处理，这里服务端发不掩码）
std::string WebSocketFrame::make_text_frame(const std::string& msg) {
    std::string frame;
    frame += char(0x81);  // FIN + Text
    size_t len = msg.size();
    if (len <= 125) {
        frame += char(len);
    } else if (len <= 65535) {
        frame += char(126);
        frame += char(len >> 8);
        frame += char(len & 0xFF);
    } else {
        frame += char(127);
        for (int i = 7; i >= 0; --i) frame += char(len >> (i*8));
    }
    frame += msg;
    return frame;
}