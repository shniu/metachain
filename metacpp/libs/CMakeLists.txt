
set(LIB_SRC hello.cpp)
add_definitions("-DLIBHELLO_BUILD")
add_library(libhello SHARED ${LIB_SRC})

set(MONGOOSE_SRC mongoose.c)
add_library(mongoose ${MONGOOSE_SRC})

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set_target_properties(libhello PROPERTIES OUTPUT_NAME "hello")
