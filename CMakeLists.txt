cmake_minimum_required(VERSION 3.25)
project(SHAMS_Events)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the Events library
add_subdirectory(Events/)

# Enable testing and add the test directory
enable_testing()

add_subdirectory(tests)