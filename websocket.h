// websocket.h
#pragma once
#include <string>
#include <unordered_map>

class WebSocketFrame {
public:
    static bool is_websocket_handshake(const std::string& request);
    static std::string make_handshake_response(const std::string& key);
    static std::string make_text_frame(const std::string& message);
    static std::string decode_frame(const char* data, int len, int& out_len);
};