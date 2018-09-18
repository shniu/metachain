
FILE(GLOB sources "*.h" "*.hpp" "*.cpp")

add_library(metacore ${sources})

#target_link_libraries(metacore ${Boost_LIBRARIES})
target_include_directories(metacore SYSTEM PRIVATE)
