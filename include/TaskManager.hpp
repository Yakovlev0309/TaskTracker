#pragma once

#include <string>
#include <vector>

#include "Task.hpp"

class TaskManager
{
public:
    void Add(const std::string& taskMsg);
    void Update(int id, const std::string& taskMsg);
    void Delete(int id);
    void UpdateStatus(int id, const Task::Status& status);
    const std::vector<Task>& GetAllTasks() const;
    std::vector<Task> GetTasksByStatus(const Task::Status& status) const;

private:
    std::vector<Task> tasks;
};
