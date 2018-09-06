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

#include "defines.h"

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
  : stopped_(false),
    socket_(io_context),
    request_(REQUEST_MAX_LEN),
    deadline_(io_context) {}
  
  void handle_write(const boost::system::error_code& error);

  void handle_read(const boost::system::error_code& error);
  
  void process_command();
  
  void send_response(const std::string& response);

  std::string create_response_from_buffer();
  
  bool stopped_;
  tcp::socket socket_;
  boost::asio::streambuf request_;
  boost::asio::deadline_timer deadline_;
};


#endif /* tcp_connection_h */
