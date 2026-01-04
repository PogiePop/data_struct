cmake_minimum_required(VERSION 3.15)
project(data_struct)



set(C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
if(MSVC)
     add_compile_options(/utf-8)
endif()

add_executable(MAIN main.c)