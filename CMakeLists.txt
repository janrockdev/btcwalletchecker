cmake_minimum_required(VERSION 3.16)
project(collector)

set(SOURCES                                  
        ${CMAKE_SOURCE_DIR}/src/main.cpp) 
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_executable(collector ${SOURCES}) 

TARGET_LINK_LIBRARIES(collector -lcurl -ljsoncpp)

target_link_directories(collector PUBLIC
                        include   
                        ${CMAKE_SOURCE_DIR}/include                        
                        ${CMAKE_SOURCE_DIR}/include/curlpp
                        ${CMAKE_SOURCE_DIR}/include/jsoncpp)