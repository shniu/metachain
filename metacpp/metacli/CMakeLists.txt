
FILE(GLOB CLI_SOURCES "*.cpp" "*.h")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(metacli ${CLI_SOURCES})

target_link_libraries(metacli  ${Boost_LIBRARIES})
