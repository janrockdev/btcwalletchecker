cmake_minimum_required(VERSION 3.16)
project(collector)
set(CMAKE_CXX_STANDARD 20)

set(SOURCES                                  
        ${CMAKE_SOURCE_DIR}/src/main.cpp)

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_path(HIREDIS_HEADER hiredis)
find_library(HIREDIS_LIB hiredis)
find_path(REDIS_PLUS_PLUS_HEADER sw)
find_library(REDIS_PLUS_PLUS_LIB redis++)

include_directories(SYSTEM ${HIREDIS_INCLUDE_DIRS})
link_directories(${HIREDIS_LIBRARY_DIRS})

add_executable(collector ${SOURCES}) 

TARGET_LINK_LIBRARIES(collector -lcurl -ljsoncpp -lhiredis ${HIREDIS_LIB} ${REDIS_PLUS_PLUS_LIB})

target_include_directories(collector PUBLIC ${HIREDIS_HEADER} ${REDIS_PLUS_PLUS_HEADER})

target_link_directories(collector PUBLIC
                        include   
                        ${CMAKE_SOURCE_DIR}/include                      
                        ${CMAKE_SOURCE_DIR}/include/curlpp
                        ${CMAKE_SOURCE_DIR}/include/jsoncpp
                        ${CMAKE_SOURCE_DIR}/include/redis-plus-plus/src/)