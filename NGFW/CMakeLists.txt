cmake_minimum_required(VERSION 3.28)
project(NGFW C)

set(CMAKE_C_STANDARD 11)

add_executable(NGFW src/main.c
        src/utility/string_replacement.h
        src/utility/string_replacement.c
        src/net/socket_io.h
        src/net/socket_io.c
        src/net/connection_handler.h
        src/net/connection_handler.c
        src/net/server.h
        src/net/server.c
        src/setings.h
        src/uthash/utarray.h
        src/uthash/uthash.h
        src/uthash/utlist.h
        src/uthash/utringbuffer.h
        src/uthash/utstack.h
        src/uthash/utstring.h
)

target_link_libraries(NGFW ws2_32)

