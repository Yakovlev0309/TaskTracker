#pragma once

#include "Storage/TaskStorage.hpp"
#include "Storage/TasksData.hpp"

class JsonTaskStorage : public TaskStorage 
{
public:
    void Save(const TasksData& data) override;
    TasksData Load() override;
};
