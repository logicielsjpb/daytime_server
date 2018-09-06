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

using boost::asio::ip::tcp;

class TCPServer
{
public:
  TCPServer(boost::asio::io_context& io_context, int port=8080);
  
private:
  void start_accept();
  
  void handle_accept(TCPConnection::pointer new_connection,
                     const boost::system::error_code& error);
  
  
  tcp::acceptor acceptor_;
};

#endif /* tcp_server_hpp */
