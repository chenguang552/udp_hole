#ifndef SOCKET_SERVICE_H
#define SOCKET_SERVICE_H

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


class service{
public:
    service(boost::asio::io_service& io_service, short port);
    ~service();

private:

    // class ClientInfo{
    // public:
    //     std::string mIp;
    //     std::string mPort;
    //     time_t mLastTime;   // 最后一次发送保持在线状态的时间
    //     ClientInfo(std::string ip,std::string port,time_t time):mIp(ip),mPort(port),mLastTime(time){}
    //     ~ClientInfo(){}
    //     // ClientInfo(std::string ip,std::string port,time_t time){
    //     //     mIp = ip;
    //     //     mPort = port;
    //     //     mLastTime = time;
    //     // }
    // };

    std::unordered_map<std::string,std::string>  mAllClientInfo;     // 所有连接过服务器的客户端记录列表
    std::unordered_map<std::string,time_t>      mOnlineClient;      // 在线用户列表，当有客户端请求此列表时 检查时间 超时客户端从此列表删除

    SOCKET::socket mService;
    SOCKET::endpoint mEndPoint;

    char mCPBuf[BUF_SIZE+1] = {0};

private:
    void do_event_choice();

    int getType(char* data);
    std::string getMsg(char* data);
    // std::string getMsg(char* data,const char* what);
     
};

#endif//!SOCKET_SERVICE_H