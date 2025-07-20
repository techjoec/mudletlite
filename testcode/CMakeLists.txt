
cmake_minimum_required(VERSION 3.10)
project(mudlet-headless)

set(CMAKE_CXX_STANDARD 17)

add_executable(mudlet-headless
    main.cpp
    telnet.cpp
    ansi.cpp
    msdp.cpp
)
if (WIN32)
    target_link_libraries(mudlet-headless ws2_32)
endif()