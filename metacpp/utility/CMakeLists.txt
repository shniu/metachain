
FILE(GLOB sources "*.h" "*.hpp" "*.cpp")

add_library(utility ${sources})

target_link_libraries(utility ${Boost_LIBRARIES})
target_include_directories(utility SYSTEM PRIVATE)