find_package(GTest REQUIRED)

include(GoogleTest)

add_executable(ShamsEventTests tests/testEvents.cpp)
target_link_libraries(ShamsEventTests PUBLIC GTest::gtest_main ShamsEvent)

gtest_discover_tests(ShamsEventTests)