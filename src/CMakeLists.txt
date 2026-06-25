add_library(tasktracker_lib
    TaskManager.cpp
)

target_include_directories(tasktracker_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_compile_features(tasktracker_lib PUBLIC cxx_std_20)

add_executable(TaskTracker
    main.cpp
)

target_link_libraries(TaskTracker PRIVATE tasktracker_lib)
