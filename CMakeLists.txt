cmake_minimum_required(VERSION 3.5.0)
project(my_ls VERSION 0.1.0 LANGUAGES C CXX)

add_executable(my_ls m_class.cpp main.cpp parse.cpp)

include(CTest)
enable_testing()