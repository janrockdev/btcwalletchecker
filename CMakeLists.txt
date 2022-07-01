cmake_minimum_required(VERSION 3.16)
project(collector)

set(SOURCES                                  
        ${CMAKE_SOURCE_DIR}/src/main.cpp) 

add_executable(collector ${SOURCES}) 

TARGET_LINK_LIBRARIES(collector -lcurl -ljsoncpp)

target_link_directories(collector PUBLIC
                        include   
                        ${CMAKE_SOURCE_DIR}/include                        
                        ${CMAKE_SOURCE_DIR}/include/curlpp
                        ${CMAKE_SOURCE_DIR}/include/jsoncpp)