#pragma once

#include "TaskStorage.hpp"
#include "TasksData.hpp"

class JsonTaskStorage : public TaskStorage 
{
public:
    void Save(const TasksData& data) override;
    TasksData Load() override;
};
