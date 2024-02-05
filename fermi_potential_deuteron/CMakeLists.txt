cmake_minimum_required(VERSION 3.10)
project(FermiMomentumDistribution VERSION 1.1)

set(CMAKE_CXX_STANDARD 17) # Use C++17 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include directories for your project
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/fermi_distribution.cpp
)

# Add executable
add_executable(fermi_momentum_distr ${SOURCES})

# Set the Vdt directory
set(VDT_INCLUDE_DIR "$ENV{ROOTSYS}/include")
set(VDT_LIBRARY "$ENV{ROOTSYS}/lib/libvdt.so") # Example
include_directories(${VDT_INCLUDE_DIR})

# Find ROOT
find_package(ROOT REQUIRED COMPONENTS Graf Gpad)
target_link_libraries(fermi_momentum_distr ${ROOT_LIBRARIES})

# Set the path to your custom Findnlohmann_json.cmake script
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Set output directory and additional compile options
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
add_compile_options(-Wall -Wextra -pedantic)
