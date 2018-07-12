include_directories(${PROJECT_SOURCE_DIR}/libs)

# set(APP_SRC main.cpp)
FILE(GLOB_RECURSE metachain_SOURCES "*.cpp")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
add_executable(metachain ${metachain_SOURCES})

target_link_libraries(metachain libhello mongoose)
