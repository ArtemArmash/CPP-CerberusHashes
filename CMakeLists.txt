cmake_minimum_required(VERSION 3.15)

project(CerberusHashes LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src/hashing)
add_subdirectory(src/file_processor)
add_subdirectory(src/main)