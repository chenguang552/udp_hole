#include "service.h"

service::service(boost::asio::io_service& io_service, short port):mService(io_service,SOCKET::udp::endpoint(SOCKET::udp::v4(),port)){do_event_choice();}

service::~service(){}

void service::do_event_choice()
{
    mService.async_receive_from(boost::asio::buffer(mCPBuf,BUF_SIZE),mEndPoint,
        [this](boost::system::error_code ec,std::size_t bytes_recvd)
        {
            if(!ec && bytes_recvd > 0)
            {
                // 解析数据  客户端依靠心跳包保持在线状态
                switch (getType(mCPBuf))
                {
                case VISIT:// 普通请求，表示在线
                    {
                        std::string ip = mEndPoint.address().to_string();
                        std::stringstream stream;
                        stream<<mEndPoint.port();
                        std::string port;
                        stream>>port;
                        time_t t;
                        time(&t);
                        // ClientInfo *clientInfo = new ClientInfo(ip,port,t);
                        // mAllClientInfo[ip] = clientInfo;
                        mAllClientInfo[ip] = port;
                        mOnlineClient[ip]=t;// 设备上线
                        std::cout << ctime(&t) <<"[" << ip << ":" <<  mAllClientInfo[ip]<< "]上线" << std::endl;
                        memset(mCPBuf,0x0,BUF_SIZE);
                        do_event_choice();
                    }
                    break;
                case NATRQ:// 穿透请求，需要服务器辅助连接到目标服务器
                    {
                        // std::cout << getMsg(mCPBuf).c_str() << "||" << mAllClientInfo["192.168.5.47"] << std::endl;
                        //  do_event_choice();
                        std::string buf = mAllClientInfo[getMsg(mCPBuf)];
                        std::cout << buf << std::endl;
                        mService.async_send_to(
                        boost::asio::buffer(buf), mEndPoint,
                            [this](boost::system::error_code,std::size_t)
                                {
                                    memset(mCPBuf,0x0,BUF_SIZE);
                                    do_event_choice();
                                }
                        );
                    }
                    break;
                case OUTLINE:// 离线请求，客户端主动下线

                    break;
                case GETLIST:// 获取p2p客户端记录列表

                    break;
                default:
                    break;
                }
                
            }
            else
            {
                do_event_choice();
            }
        }
    );
}

int service::getType(char* data)
{
    std::string strData(data,TYPELEN);
    std::stringstream strDataStream(strData);
    int result;
    strDataStream>>result;
    std::cout << result << std::endl;
    return result;
}

// std::string service::getMsg(char* data_,const char* what)
std::string service::getMsg(char* data)
{
    std::stringstream strDataStream(data+TYPELEN+1);
    std::string hopeIp2;
    strDataStream>>hopeIp2;
    return hopeIp2;
}