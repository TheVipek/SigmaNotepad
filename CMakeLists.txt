CMAKE_MINIMUM_REQUIRED(VERSION 3.2...3.28)

project(SigmaNotepad
        VERSION 0.1
        DESCRIPTION ""
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set(SDL2_PATH ${CMAKE_SOURCE_DIR}/libs/SDL2)
set(SDL2_LIBRARY ${CMAKE_SOURCE_DIR}/libs/SDL2/lib/libSDL2.a)

message(${SDL2_PATH})

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})


add_executable(SigmaNotepad main.cpp)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})