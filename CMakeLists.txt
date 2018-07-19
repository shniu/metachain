cmake_minimum_required(VERSION 3.0)
project(metachain)

SET(CMAKE_CXX_COMPILER "/usr/bin/c++")

message(${PROJECT_BINARY_DIR})
message(${PROJECT_SOURCE_DIR})
message(${CMAKE_CXX_COMPILER_ID})
message(${CMAKE_CXX_COMPILER_VERSION})

SET(CMAKE_VERBOSE_MAKEFILE 1)
set(CMAKE_CXX_STANDARD 14)

# ----- style 1
#set(LIB_SRC hello.cpp)
#set(APP_SRC main.cpp)
#
#add_library(libhello ${LIB_SRC})
#
#set(SRC_LIST main.cpp hello.cpp)
#
#add_executable(metachain ${SRC_LIST})
#
#target_link_libraries(metachain libhello)
#set_target_properties(libhello PROPERTIES OUTPUT_NAME "hello")

# ----- style 2
add_subdirectory(src)
add_subdirectory(libs)
