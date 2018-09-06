//
// server.cpp
// ~~~~~~~~~~
//
// Create a DayTime server using boost asio library. The server responds to
// three commands:
//   - date: return the current date in format yyyy-mm-dd
//   - time: return the current time in format hh:mm:ss, timezone
//   - datetime: return the current date and time in format yyyy-mm-ddhh:mm:ss, timezone
//
// Based on 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <boost/asio.hpp>
#include "tcp_server.hpp"
#include "udp_server.hpp"
#include "defines.h"

int main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cerr << "Usage: daytime_server <port>" << std::endl;
    return 1;
  }
  
  try {
    int port = atoi(argv[1]);
  
    boost::asio::io_context io_context;
    std::cout << "Starting TCP Server on port " << port << std::endl;
    TCPServer server1(io_context, port);
    std::cout << "Starting UDP Server on port " << port << std::endl;
    UDPServer server2(io_context, port);
    io_context.run();
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  
  return 0;
}
