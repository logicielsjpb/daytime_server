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

class RequestParser {
public:
  static std::string parse(const std::string& request)
  {
    using std::chrono::system_clock;
    std::time_t tt = system_clock::to_time_t (system_clock::now());
    std::stringstream ssTp;
    struct std::tm * ptm = std::localtime(&tt);
  
    if (request.compare("date") == 0) {
      ssTp << std::put_time(ptm,"%F");
      return ssTp.str();
    }
  
    if (request.compare("time") == 0) {
      ssTp << std::put_time(ptm,"%T, %Z");
      return ssTp.str();
    }

    if (request.compare("datetime") == 0) {
      ssTp << std::put_time(ptm,"%F%T, %Z");
      return ssTp.str();
    }
  
    return NULL; // Invalid command
  }
};

#endif /* request_parser_hpp */
