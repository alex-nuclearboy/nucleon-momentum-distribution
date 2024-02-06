cmake_minimum_required(VERSION 3.10)
project(HeliumMomentumDistribution VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include directories for your project
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/MomentumDataLoader.cpp
    src/GraphGenerator.cpp
)

# Add executable
add_executable(HeliumMomentumDist ${SOURCES})

# Set the Vdt directory
set(VDT_INCLUDE_DIR "$ENV{ROOTSYS}/include")
set(VDT_LIBRARY "$ENV{ROOTSYS}/lib/libvdt.so")
include_directories(${VDT_INCLUDE_DIR})

# Find ROOT
find_package(ROOT REQUIRED COMPONENTS Graf Gpad)
target_link_libraries(HeliumMomentumDist ${ROOT_LIBRARIES})

# Set the path to your custom Findnlohmann_json.cmake script
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Set output directory and additional compile options
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
add_compile_options(-Wall -Wextra -pedantic)
