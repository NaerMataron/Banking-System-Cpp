cmake_minimum_required(VERSION 3.30)
project(MyBankingSystem)

set(CMAKE_CXX_STANDARD 23)
include_directories(${CMAKE_SOURCE_DIR}/External/include)

add_executable(MyBankingSystem main.cpp)
