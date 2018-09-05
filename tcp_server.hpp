//
//  tcp_server.hpp
//  daytime_server
//
//  Created by Jean-Philippe Boily on 2018-09-05.
//

#ifndef tcp_server_hpp
#define tcp_server_hpp

#include "tcp_connection.hpp"

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <vector>

using boost::asio::ip::tcp;

class TCPServer
{
public:
  TCPServer(boost::asio::io_context& io_context, int port=8080);
  typedef std::vector<TCPConnection::pointer> ConnList;
  
private:
  void start_accept();
  
  void handle_accept(TCPConnection::pointer new_connection,
                     const boost::system::error_code& error);
  
  void close_connections();
  
  tcp::acceptor acceptor_;
  ConnList connections_;
};

#endif /* tcp_server_hpp */
