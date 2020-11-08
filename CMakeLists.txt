cmake_minimum_required(VERSION 3.17)
project(RSA)

set(CMAKE_CXX_STANDARD 14)

add_executable(RSA main.cpp src/BigInteger.cpp src/BigInteger.h src/RSA.cpp src/RSA.h)
add_executable(Test test/main_test.cpp src/BigInteger.cpp src/BigInteger.h)