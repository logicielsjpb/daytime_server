//
//  udp_server.hpp
//  daytime_server
//
//  Created by Jean-Philippe Boily on 2018-09-05.
//

#ifndef udp_server_hpp
#define udp_server_hpp

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

class UDPServer
{
public:
  UDPServer(boost::asio::io_context& io_context, int port=8080);
  
private:
  void start_receive();
  
  void handle_receive(const boost::system::error_code& error);
  
  void handle_send(boost::shared_ptr<std::string>);
  
  udp::socket socket_;
  udp::endpoint remote_endpoint_;
  boost::array<char, 1> recv_buffer_;
};

#endif /* udp_server_hpp */
