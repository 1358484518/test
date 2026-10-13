cmake_minimum_required(VERSION 3.5)

project(qt-mdns LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build QMdnsEngine as a static library" FORCE)

find_package(Qt5 5.14 REQUIRED COMPONENTS Core Network)

add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../third_party/qmdnsengine
    ${CMAKE_CURRENT_BINARY_DIR}/qmdnsengine
)

add_executable(qt-mdns
    main.cpp
    mdnsdemo.cpp
    mdnsdemo.h
)

target_link_libraries(qt-mdns PRIVATE qmdnsengine Qt5::Core Qt5::Network)
