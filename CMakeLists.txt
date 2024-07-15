cmake_minimum_required(VERSION 3.16)

project(SHAMS_Events)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add other cmake files
include(cmake/install_libs.cmake)

# Add the Events library
add_subdirectory(ShamsEvent/)

# Enable testing and add the test directory
if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
	enable_testing()
	add_subdirectory(test)
endif()