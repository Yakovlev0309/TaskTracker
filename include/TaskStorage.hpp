#pragma once

#include "Task.hpp"
#include "TasksData.hpp"

#include <unordered_map>

class TaskStorage
{
public:
    virtual void Save(const TasksData& data) = 0;
    virtual TasksData Load() = 0;
};
