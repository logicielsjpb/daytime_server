//
//  tcp_connection.cpp
//  daytime_server
//
//  Created by Jean-Philippe Boily on 2018-09-05.
//
#include "tcp_connection.hpp"
#include <sstream>
#include <iostream>

void TCPConnection::start()
{
  // Read request
  boost::asio::read_until(socket_, request, '\n');
  
  std::string daytime_val = create_response_from_buffer(request);
  std::cout << "Current daytime val is: " << daytime_val << std::endl;
  // Write response
  if (!daytime_val.empty()) {
    boost::asio::async_write(socket_, boost::asio::buffer(daytime_val),
                             boost::bind(&TCPConnection::handle_write, shared_from_this()));
  }
}


void TCPConnection::handle_write()
{
}

void TCPConnection::handle_read(const boost::system::error_code& error, size_t bytes_transferred) {
  
}

void TCPConnection::stop() {
  
}

std::string create_response_from_buffer(boost::asio::streambuf req)  {
  std::istream request_stream(&req);
  std::string command;
  request_stream >> command;
  
  return RequestParser::parse(command);
}

