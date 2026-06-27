#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <ranges>

#include "Task.hpp"
#include "Storage/JsonTaskStorage.hpp"

class TaskManager
{
public:
    TaskManager();

    int Add(const std::string& taskMsg);
    void Delete(int id);
    void UpdateDescription(int id, const std::string& taskMsg);
    void UpdateStatus(int id, const Task::Status& status);

    const std::unordered_map<int, Task>& GetAllTasks() const { return tasks; }
    auto GetTasksByStatus(const Task::Status& status) const
    {
        return tasks | std::views::filter(
            [status](const std::pair<int, Task>& item) {
                return item.second.status == status;
            }
        );
    }

    Task& GetTaskById(int id);
    
private:
    void UpdateStorage();

    std::unordered_map<int, Task> tasks;
    int nextId = 1;

    JsonTaskStorage storage;
};
