cmake_minimum_required(VERSION 3.10)
project(NucleonMomentumDistribution VERSION 2.0 DESCRIPTION "Nucleon Momentum Distribution" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# General settings
include_directories(${PROJECT_SOURCE_DIR}/include)

# Set the Vdt directory
set(VDT_INCLUDE_DIR "$ENV{ROOTSYS}/include")
set(VDT_LIBRARY "$ENV{ROOTSYS}/lib/libvdt.so")
include_directories(${VDT_INCLUDE_DIR})

# Set the ROOT 
find_package(ROOT REQUIRED COMPONENTS Graf Gpad)
include_directories(${ROOT_INCLUDE_DIRS})

# Source files for the deuteron and helium analyses
set(DEUTERON_SOURCES 
    main.cpp 
    src/deuteron/momentum_distribution.cpp 
    src/deuteron/plot_generator_deuteron.cpp)

set(HELIUM_SOURCES 
    main.cpp 
    src/helium/momentum_data_loader.cpp 
    src/helium/plot_generator_helium.cpp)

# Executable for deuteron
add_executable(deuteron_momentum_distribution ${DEUTERON_SOURCES})
target_compile_definitions(deuteron_momentum_distribution PRIVATE DEUTERON)
target_link_libraries(deuteron_momentum_distribution PRIVATE ${ROOT_LIBRARIES})

# Executable for helium
add_executable(helium_momentum_distribution ${HELIUM_SOURCES})
target_compile_definitions(helium_momentum_distribution PRIVATE HELIUM)
target_link_libraries(helium_momentum_distribution PRIVATE ${ROOT_LIBRARIES})

# Optionally, set the output directory for executables
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

# Compilation options for additional warnings and standards compliance
add_compile_options(-Wall -Wextra -pedantic)

# Documentation generation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    add_custom_target(doc ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
endif()
