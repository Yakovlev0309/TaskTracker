#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "Task.hpp"
#include "JsonTaskStorage.hpp"

class TaskManager
{
public:
    TaskManager();

    int Add(const std::string& taskMsg);
    void Delete(int id);
    void UpdateTitle(int id, const std::string& taskMsg);
    void UpdateStatus(int id, const Task::Status& status);

    const std::unordered_map<int, Task>& GetAllTasks() const;
    std::vector<std::pair<int, Task>> GetTasksByStatus(const Task::Status& status) const;
    Task GetTaskById(int id) const;

private:
    void UpdateStorage();

    std::unordered_map<int, Task> tasks;
    int nextId = 1;

    JsonTaskStorage storage;
};
