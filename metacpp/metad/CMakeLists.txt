
FILE(GLOB sources "*.hpp" "*.cpp" "*.h")

add_executable(metad ${sources})
target_link_libraries(
        metad
        PRIVATE metacore p2p ${Boost_LIBRARIES}
)
