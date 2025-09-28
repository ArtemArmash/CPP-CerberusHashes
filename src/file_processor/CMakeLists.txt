add_library(file_processor_lib STATIC
    FileProcessor.cpp
)
target_link_libraries(file_processor_lib PUBLIC hashing_lib)

target_include_directories(file_processor_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})