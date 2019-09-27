#include <cstdlib>
#include <iostream>
#include <sstream>
#include <boost/asio.hpp>
#include "service.h"
 
using boost::asio::ip::udp;
 
int main(int argc, char* argv[])
{
    std::cout << "begin" << std::endl;
    try
    {
        boost::asio::io_service io_service;
        service server(io_service, 2280);
        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
 
    return 0;
}