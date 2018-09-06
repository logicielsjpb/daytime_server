//
//  tcp_connection.cpp
//  daytime_server
//
//  Created by Jean-Philippe Boily on 2018-09-05.
//
#include "tcp_connection.hpp"
#include "request_parser.hpp"
#include <iostream>

using boost::asio::deadline_timer;

void TCPConnection::start()
{
  // Read request
  process_command();
}


void TCPConnection::handle_write(const boost::system::error_code& error)
{
  if (!error) {
    // Read next command if no errors
    process_command();
  }
}

void TCPConnection::handle_read(const boost::system::error_code& error)
{
  if (!error) {
    send_response(get_response());
  } else {
    stop();
  }
}

void TCPConnection::process_command()
{
  deadline_.expires_from_now(boost::posix_time::seconds(SOCKET_TIMEOUT));

  // TODO - We might need to be more flexible on the line ending used.
  boost::asio::async_read_until(socket_, request_, '\n',
                                boost::bind(&TCPConnection::handle_read,
                                            shared_from_this(),
                                            boost::asio::placeholders::error));
}

void TCPConnection::send_response(const std::string& response)
{
  if (response.empty()) {
    process_command();
  } else {
    std::cout << "(TCPConnection " << this << ") Sending response: " << response << std::endl;
    boost::asio::async_write(socket_, boost::asio::buffer(response),
                             boost::bind(&TCPConnection::handle_write,
                                         shared_from_this(),
                                         boost::asio::placeholders::error));
  }
}

void TCPConnection::stop()
{
  std::cout << "(TCPConnection " << this << ") Connection timeout." << std::endl;
  boost::system::error_code ignored_ec;
  socket_.close(ignored_ec);
  deadline_.cancel();
}

std::string TCPConnection::get_response()
{
  std::istream request_stream(&request_);
  std::string command;
  request_stream >> command;
  
  return RequestParser::parse(command);
}

