cmake_minimum_required(VERSION 2.6)
project(sbox)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -g")

add_library(tpt SHARED tpt.c)
add_library(mdom SHARED mdom.c)
add_library(kernel_api SHARED kernel_api.c)
add_library(sbox SHARED tpt.c mdom.c kernel_api.c)

target_link_libraries(sbox tpt mdom kernel_api pthread) 

