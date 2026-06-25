#pragma once

#include "TaskStorage.hpp"

class JsonTaskStorage : public TaskStorage 
{
public:
    void Save(const std::unordered_map<int, Task>& tasks) override;
    std::unordered_map<int, Task> Load() override;
};
