add_executable(TaskManagerTests
    TaskManagerTests.cpp
)

target_link_libraries(TaskManagerTests
    PRIVATE
    tasktracker_lib
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(TaskManagerTests)
