//
//  tcp_server.cpp
//  daytime_server
//
//  Created by Jean-Philippe Boily on 2018-09-05.
//

#include "tcp_server.hpp"

TCPServer::TCPServer(boost::asio::io_context& io_context, int port)
: acceptor_(io_context, tcp::endpoint(tcp::v6(), port))
{
  start_accept();
}

void TCPServer::start_accept()
{
  TCPConnection::pointer new_connection =
  TCPConnection::create(acceptor_.get_executor().context());
  
  acceptor_.async_accept(new_connection->socket(),
                         boost::bind(&TCPServer::handle_accept, this, new_connection,
                                     boost::asio::placeholders::error));
}

void TCPServer::handle_accept(TCPConnection::pointer new_connection,
                   const boost::system::error_code& error)
{
  if (!error) {
    connections_.push_back(new_connection);
  
    // TODO - Start threads to handle multiple connections
    // TODO - Add timeout
    new_connection->start();
  }
  
  start_accept();
}

void TCPServer::close_connections() {
  for (ConnList::iterator it = connections_.begin(); it != connections_.end(); ++it) {
    (*it)->stop();
  }
}
