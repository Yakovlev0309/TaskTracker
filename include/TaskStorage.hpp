#pragma once

#include "Task.hpp"

#include <unordered_map>

class TaskStorage
{
public:
    virtual void Save(const std::unordered_map<int, Task>& tasks) = 0;
    virtual std::unordered_map<int, Task> Load() = 0;
};
