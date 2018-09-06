cmake_minimum_required(VERSION 2.8)
project(daytime_app)

find_package(Boost 1.68.0 REQUIRED system)

include_directories(${Boost_INCLUDE_DIR})
add_executable(daytime_server server.cpp)

target_link_libraries(daytime_server ${Boost_LIBRARIES})


install(TARGETS daytime_server DESTINATION bin)
