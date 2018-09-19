enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ".")
set(PROJECT_UNIT_TEST_NAME ${PROJECT_NAME}_unit_tests)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

file(GLOB TESTS_SRC ${PROJECT_SOURCE_DIR}/tests/*.cpp)

#add_executable(${PROJECT_UNIT_TEST_NAME} ${UNIT_TESTS_SRC_FILES})
#target_link_libraries(${PROJECT_UNIT_TEST_NAME} ${Boost_LIBRARIES})
#add_test(MetaCTest ${PROJECT_UNIT_TEST_NAME})

foreach(testSrc ${TESTS_SRC})
    get_filename_component(testName ${testSrc} NAME_WE)
    # message(${testName})
    add_executable(${testName} ${testSrc})
    target_link_libraries(${testName}
            ${Boost_LIBRARIES}
            metacore
            p2p
    )
    set(${testName} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY
            ${CMAKE_CURRENT_SOURCE_DIR}/testBin)
    add_test(NAME ${testName}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testBin
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/testBin/${testName})
endforeach()
