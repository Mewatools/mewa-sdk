cmake_minimum_required(VERSION 3.10)
project(starsmodule VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)
find_package(PkgConfig REQUIRED)


# Find GLX (part of OpenGL on Linux)
find_library(GLX_LIBRARY NAMES GL GLX)
if(NOT GLX_LIBRARY)
    message(FATAL_ERROR "GLX library not found")
endif()


include(${CMAKE_SOURCE_DIR}/src/stars.cmake)


include(${CMAKE_SOURCE_DIR}/../../framework/framework.cmake)

# Create executable with Mewa dependencies
add_executable(starsmodule ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(starsmodule 
    ${OPENGL_LIBRARIES}
    ${X11_LIBRARIES}
    ${GLX_LIBRARY}
)

# Include directories
target_include_directories(starsmodule PRIVATE
    ${OPENGL_INCLUDE_DIRS}
    ${X11_INCLUDE_DIRS}
)

# Compiler definitions
target_compile_options(starsmodule PRIVATE )

# Set output directory
set_target_properties(starsmodule PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Installation
install(TARGETS starsmodule
    RUNTIME DESTINATION bin
)

# Print configuration info
message(STATUS "OpenGL libraries: ${OPENGL_LIBRARIES}")
message(STATUS "X11 libraries: ${X11_LIBRARIES}")
message(STATUS "GLX library: ${GLX_LIBRARY}")
