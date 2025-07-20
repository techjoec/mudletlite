cmake_minimum_required(VERSION 3.10)
project(mudlet-headless-full)

set(CMAKE_CXX_STANDARD 17)

add_executable(mudlet-headless
    main.cpp
    telnet.cpp
    ansi.cpp
    msdp.cpp
    lua_engine.cpp
    parser.cpp
)
