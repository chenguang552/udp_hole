#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <stdarg.h>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <boost/format.hpp>
#include <stdlib.h>
#include <sstream>
#include <time.h>
#include <vector>
#include <unordered_map>

#define SOCKET boost::asio::ip::udp
#define BUF_SIZE 1024

// xxxxxxxx -type 8bit xxxx-xxxx-xxxx-xxxx -req_ipv4 16bit xxxxxxxx -req_port 8bit
#define TYPELEN 2

// REQTYPE
#define VISIT 0
#define NATRQ 1
#define OUTLINE 2
#define GETLIST 3
class client{
public:
    client(boost::asio::io_service& io_service, short port);
    ~client();
private:
    void udp_header();
    void get_port();
    void say_hello(int port);

private:
    SOCKET::socket mService;
    SOCKET::endpoint mEndPoint;

    char mCPBuf[BUF_SIZE+1] = {0};
};

#endif//!SOCKET_CLIENT_H