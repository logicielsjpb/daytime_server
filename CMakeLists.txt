cmake_minimum_required(VERSION 2.8)
project(daytime_app)

find_package(Boost 1.68.0 REQUIRED system)

include_directories(${Boost_INCLUDE_DIR})
add_executable(daytime_server server.cpp)
add_executable(daytime_client_udp client_udp.cpp)
add_executable(daytime_client_tcp client_tcp.cpp)

target_link_libraries(daytime_server ${Boost_LIBRARIES})
target_link_libraries(daytime_client_udp ${Boost_LIBRARIES})
target_link_libraries(daytime_client_tcp ${Boost_LIBRARIES})


install(TARGETS daytime_server DESTINATION bin)
install(TARGETS daytime_client_udp DESTINATION bin)
install(TARGETS daytime_client_tcp DESTINATION bin)
