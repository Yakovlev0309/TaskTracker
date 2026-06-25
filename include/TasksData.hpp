#pragma once

#include <unordered_map>

#include "Task.hpp"

struct TasksData
{
    std::unordered_map<int, Task> tasks;
    int nextId = -1;
};
