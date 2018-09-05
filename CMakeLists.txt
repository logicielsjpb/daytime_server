cmake_minimum_required(VERSION 2.8)
project(daytime_server)
add_executable(daytime_server main.cpp)
install(TARGETS daytime_server DESTINATION bin)
