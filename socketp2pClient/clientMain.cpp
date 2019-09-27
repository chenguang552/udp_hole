#include <cstdlib>
#include <iostream>
#include <sstream>
#include <boost/asio.hpp>
#include "client.h"
 
using boost::asio::ip::udp;
 
int main(int argc, char* argv[])
{
    std::cout << "begin" << std::endl;
    try
    {
        boost::asio::io_service io_service;
        client client_(io_service, 12345);
        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
 
    return 0;
}