add_library(hashing_lib STATIC
    md5.cpp
    sha1.cpp
    sha256.cpp
)   
target_include_directories(hashing_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})