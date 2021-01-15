cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")

set(CLIENT_SRC_FILES
        localSocketClient.cpp
)

set(SERVER_SRC_FILES
        localSocketServer.cpp
)

add_executable(test_local_socket_client ${CLIENT_SRC_FILES})
add_executable(test_local_socket_server ${SERVER_SRC_FILES})

install(TARGETS test_local_socket_client
        RUNTIME
        DESTINATION /usr/bin
)

install(TARGETS test_local_socket_server
        RUNTIME
        DESTINATION /usr/bin
)