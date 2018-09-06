//
//  request_parser.hpp
//  daytime_server
//
//  Created by Jean-Philippe Boily on 2018-09-05.
//

#ifndef request_parser_hpp
#define request_parser_hpp

#include <string>
#include <vector>
#include <iomanip>      // std::put_time
#include <ctime>        // std::time_t, struct std::tm, std::localtime
#include <sstream>      // std::stringstream, std::stringbuf
#include "command.hpp"

namespace RequestParser {

  static std::string parse(const std::string& request)
  {
    // TODO - It might be a good idea to move the response generation from the parser
    using std::chrono::system_clock;
    std::time_t tt = system_clock::to_time_t (system_clock::now());
    std::stringstream ssTp;
    struct std::tm * ptm = std::localtime(&tt);
    Command::CmdMap::iterator cmd = Command::commands_.find(request);
  
    if (cmd == Command::commands_.end()) {
      return "Invalid Command"; // We could respond with an error code to the client
    }
  
    ssTp << std::put_time(ptm,(*cmd).second) << std::endl;
  
    return ssTp.str();
  }
};

#endif /* request_parser_hpp */
