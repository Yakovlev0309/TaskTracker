#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "Task.hpp"

class TaskManager
{
public:
    void Add(const std::string& taskMsg);
    void Update(int id, const std::string& taskMsg);
    void Delete(int id);
    void UpdateStatus(int id, const Task::Status& status);

    const std::unordered_map<int, Task>& GetAllTasks() const;
    std::vector<Task> GetTasksByStatus(const Task::Status& status) const;
    Task GetTaskById(int id) const;

private:
    std::unordered_map<int, Task> tasks;
    int nextId = 1;
};
