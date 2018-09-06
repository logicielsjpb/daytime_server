//
//  udp_server.cpp
//  daytime_server
//
//  Created by Jean-Philippe Boily on 2018-09-05.
//

#include <string>
#include <iostream>
#include "udp_server.hpp"
#include "request_parser.hpp"

UDPServer::UDPServer(boost::asio::io_context& io_context, int port)
: socket_(io_context, udp::endpoint(udp::v6(), port))
{
  start_receive();
}

void UDPServer::start_receive()
{
  socket_.async_receive_from(boost::asio::buffer(recv_buffer_), remote_endpoint_,
                             boost::bind(&UDPServer::handle_receive, this,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

void UDPServer::handle_receive(const boost::system::error_code& error, std::size_t bytes)
{
  if (!error || error == boost::asio::error::message_size) {
    std::string request = buffer_to_str(bytes);
    std::cout << "(UDPServer) " << "Received message: " << request << std::endl;
    std::string message(RequestParser::parse(request));
  
    socket_.async_send_to(boost::asio::buffer(message), remote_endpoint_,
                          boost::bind(&UDPServer::handle_send, this,
                                      boost::asio::placeholders::error));
    
    start_receive();
  }
}

void UDPServer::handle_send(const boost::system::error_code& error)
{
  if (error) {
    std::cout << "(UDPServer " << this << ") response not sent: " << error << std::endl;
  }
  
  start_receive();
}

std::string UDPServer::buffer_to_str(std::size_t bytes)
{
  std::string data;
  std::copy(recv_buffer_.begin(), recv_buffer_.begin()+bytes, std::back_inserter(data));
  data.erase(std::remove(data.begin(), data.end(), '\n'), data.end());
  return data;
}
