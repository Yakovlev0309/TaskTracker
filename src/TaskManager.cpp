#include "TaskManager.hpp"

#include <algorithm>
#include <stdexcept>

TaskManager::TaskManager()
{
    tasks = storage.Load();
}

int TaskManager::Add(const std::string& taskMsg)
{
    tasks.emplace(nextId, Task(taskMsg));
    
    UpdateStorage();

    return nextId++;
}

void TaskManager::Update(int id, const std::string& taskMsg)
{
    if (!tasks.contains(id))
        throw std::out_of_range("Failed to update task title: Invalid task id.");

    tasks.at(id).title = taskMsg;

    UpdateStorage();
}

void TaskManager::Delete(int id)
{
    if (!tasks.contains(id))
        throw std::out_of_range("Failed to delete task: Invalid task id.");

    tasks.erase(id);

    UpdateStorage();
}

void TaskManager::UpdateStatus(int id, const Task::Status& status)
{
    if (!tasks.contains(id))
        throw std::out_of_range("Failed to update task status: Invalid task id.");

    tasks.at(id).status = status;

    UpdateStorage();
}

const std::unordered_map<int, Task>& TaskManager::GetAllTasks() const
{
    return tasks;
}

std::vector<Task> TaskManager::GetTasksByStatus(const Task::Status& status) const
{
    std::vector<Task> result;
    std::for_each(tasks.begin(), tasks.end(), [&status, &result](const std::pair<int, Task>& task){
        if (task.second.status == status)
            result.push_back(task.second);
    });
    return result;
}

Task TaskManager::GetTaskById(int id) const
{
    auto it = tasks.find(id);

    if (it == tasks.end())
        throw std::out_of_range("Failed to get task: Invalid task id.");

    return it->second;
}

void TaskManager::UpdateStorage()
{
    storage.Save(tasks);
}
