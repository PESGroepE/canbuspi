cmake_minimum_required(VERSION 3.23)
project(canbuspi)

set(CMAKE_CXX_STANDARD 11)

add_executable(canbuspi main.cpp Canbus.cpp Canbus.h TCPSocket.cpp TCPSocket.h)
