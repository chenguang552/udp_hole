#include "client.h"
client::client(boost::asio::io_service& io_service, short port):mService(io_service,SOCKET::udp::endpoint(SOCKET::udp::v4(),port))
{
    udp_header();
}

client::~client(){}

void client::udp_header()
{
     mService.async_send_to(
        boost::asio::buffer("00"), SOCKET::endpoint(boost::asio::ip::address_v4::from_string("207.246.121.35"), 2280),
        [this](boost::system::error_code,std::size_t)
        {
            get_port();
        }
    );
}

void client::get_port()
{
    mService.async_send_to(
        boost::asio::buffer("01 61.158.146.151"), SOCKET::endpoint(boost::asio::ip::address_v4::from_string("207.246.121.35"), 2280),
        [this](boost::system::error_code,std::size_t)
        {
            memset(mCPBuf,0x0,BUF_SIZE);
            mService.async_receive_from(boost::asio::buffer(mCPBuf,BUF_SIZE),mEndPoint,
            [this](boost::system::error_code ec,std::size_t bytes_recvd)
            {
                say_hello(atoi(mCPBuf));
            });
        });  
    
}

void client::say_hello(int port)
{
    
    mService.async_send_to(
        boost::asio::buffer("hello\n"), SOCKET::endpoint(boost::asio::ip::address_v4::from_string("61.158.146.151"), port),
        [this](boost::system::error_code,std::size_t)
        {
            sleep(10);
            say_hello(atoi(mCPBuf));
        });
}