//
//  command.h
//  daytime_server
//
//  Created by Jean-Philippe Boily on 2018-09-06.
//

#ifndef command_h
#define command_h

#include <string>
#include <map>

class Command {
public:
  // Map of available commands with their time format
  typedef std::map<std::string, const char*> CmdMap;
  static CmdMap commands_;
  
private:
  static CmdMap init_map()
  {
    CmdMap cmd_map;
    cmd_map.insert(std::pair<std::string, const char*>("date", "%F"));
    cmd_map.insert(std::pair<std::string, const char*>("time", "%T, %Z"));
    cmd_map.insert(std::pair<std::string, const char*>("datetime", "%F%T, %Z"));

    return cmd_map;
  }
};

#endif /* command_h */
