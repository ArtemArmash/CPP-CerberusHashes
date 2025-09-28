add_executable(cerberus
    main.cpp
)
find_package(Threads REQUIRED)

target_link_libraries(cerberus PRIVATE
    file_processor_lib
    Threads::Threads
)