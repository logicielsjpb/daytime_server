//
//  tcp_connection.hpp
//  daytime_server
//
//  Created by Jean-Philippe Boily on 2018-09-05.
//

#ifndef tcp_connection_h
#define tcp_connection_h

#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>

#include "request_parser.hpp"

using boost::asio::ip::tcp;

class TCPConnection
: public boost::enable_shared_from_this<TCPConnection>
{
public:
  typedef boost::shared_ptr<TCPConnection> pointer;
  
  static pointer create(boost::asio::io_context& io_context)
  {
    return pointer(new TCPConnection(io_context));
  }

  tcp::socket& socket() { return socket_; };
  
  void start();
  
  void stop();
  
private:
  TCPConnection(boost::asio::io_context& io_context)
  : socket_(io_context) {}
  
  void handle_write();
  
  void handle_read(const boost::system::error_code& error, size_t bytes_transferred);

  std::string create_response_from_buffer(boost::asio::streambuf req);
  
  tcp::socket socket_;
  boost::asio::streambuf request;
};


#endif /* tcp_connection_h */
