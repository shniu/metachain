
FILE(GLOB sources "*.h" "*.hpp" "*.cpp")

add_library(p2p ${sources})

target_link_libraries(p2p utility ${Boost_LIBRARIES})
target_include_directories(p2p SYSTEM PRIVATE)