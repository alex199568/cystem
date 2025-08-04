# CMakeLists.txt in your project root
cmake_minimum_required(VERSION 3.24)

# Give the project a name
project(cystem)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Ot /fp:fast /arch:AVX2")

# List your source files explicitly.  CMake docs recommend this
# rather than globbing so that the build system knows when to regenerate:contentReference[oaicite:0]{index=0}.
set(SRC_FILES
    src/main.cpp
    src/color.cpp
    src/image.cpp
    src/matrix.cpp
    src/point.cpp
    src/vector.cpp
)

# Define an executable target named "cystem" from the listed files
add_executable(cystem ${SRC_FILES})

# Tell CMake to put the resulting executable in the build directory
set_target_properties(cystem PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build
)