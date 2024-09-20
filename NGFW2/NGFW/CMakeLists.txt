cmake_minimum_required(VERSION 3.28)
project(NGFW C)

set(CMAKE_C_STANDARD 11)

add_executable(NGFW src/main.c
        src/main.h
        src/service/SocketTcpListener.c
        src/service/SocketTcpListener.h
        src/service/SocketTcpSender.c
        src/service/SocketTcpSender.h
        src/thread/threadListen.c
        src/thread/threadListen.h
        src/thread/threadSend.c
        src/thread/threadSend.h
        src/thread/threadSendToCarbon.c
        src/thread/threadSendToCarbon.h
        src/thread_value/counters.h
        src/thread_value/gauges.h
        src/thread_value/stats.c
        src/thread_value/stats.h
        src/thread_value/timers.h
        src/uthash/utarray.h
        src/uthash/uthash.h
        src/uthash/utlist.h
        src/uthash/utringbuffer.h
        src/uthash/utstack.h
        src/uthash/utstring.h
        src/service/SocketData.h
)
target_link_libraries(NGFW ws2_32)
