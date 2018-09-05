//
//  udp_server.cpp
//  daytime_server
//
//  Created by Jean-Philippe Boily on 2018-09-05.
//

#include "udp_server.hpp"
#include <string>

UDPServer::UDPServer(boost::asio::io_context& io_context, int port)
: socket_(io_context, udp::endpoint(udp::v6(), port))
{
  start_receive();
}

void UDPServer::start_receive()
{
  socket_.async_receive_from(
                             boost::asio::buffer(recv_buffer_), remote_endpoint_,
                             boost::bind(&UDPServer::handle_receive, this,
                                         boost::asio::placeholders::error));
}

void UDPServer::handle_receive(const boost::system::error_code& error)
{
  if (!error || error == boost::asio::error::message_size)
  {
    // TODO - Use Message builder
    boost::shared_ptr<std::string> message(new std::string("Test"));
    
    socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_,
                          boost::bind(&UDPServer::handle_send, this, message));
    
    start_receive();
  }
}

void UDPServer::handle_send(boost::shared_ptr<std::string> /*message*/)
{
}
