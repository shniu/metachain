
FILE(GLOB HEADERS "${PROJECT_SOURCE_DIR}/include/network/*.h")
FILE(GLOB LIB_SOURCES "*.cpp" "*.c")

set(LIB_SRC ${LIB_SOURCES} ${HEADERS})

add_definitions("-DLIBHELLO_BUILD")
add_library(libnetwork SHARED ${LIB_SRC})

set(MONGOOSE_SRC mongoose.c)
add_library(mongoose ${MONGOOSE_SRC})

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set_target_properties(libnetwork PROPERTIES OUTPUT_NAME "libnetwork")
