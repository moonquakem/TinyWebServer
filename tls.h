#pragma once
#include <openssl/ssl.h>
#include <openssl/err.h>

class TLSContext {
public:
    TLSContext();
    ~TLSContext();
    SSL* accept_ssl(int client_fd);
    void close_ssl(SSL* ssl);

    SSL_CTX* ctx = nullptr;
};