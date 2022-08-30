cmake_minimum_required(VERSION 3.23)
project(http_simple_server)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules")

find_package(Libevent REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(http_simple_server main.cpp)
target_link_libraries(http_simple_server
        PUBLIC
        ${LIBEVENT_LIB}
        )

target_include_directories(http_simple_server
        PUBLIC
        ${LIBEVENT_INCLUDE_DIR}
        )
