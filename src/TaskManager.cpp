#include "TaskManager.hpp"
#include "TasksData.hpp"

#include <algorithm>
#include <stdexcept>

TaskManager::TaskManager()
{
    TasksData data = storage.Load();
    tasks = std::move(data.tasks);
    nextId = data.nextId;
}

int TaskManager::Add(const std::string& taskMsg)
{
    tasks.emplace(nextId, Task(taskMsg));
    
    ++nextId;
    UpdateStorage();

    return nextId - 1;
}

void TaskManager::Delete(int id)
{
    if (!tasks.contains(id))
        throw std::out_of_range("Failed to delete task: Invalid task id.");

    tasks.erase(id);

    UpdateStorage();
}

void TaskManager::UpdateTitle(int id, const std::string& taskMsg)
{
    if (!tasks.contains(id))
        throw std::out_of_range("Failed to update task title: Invalid task id.");

    tasks.at(id).title = taskMsg;

    UpdateStorage();
}

void TaskManager::UpdateStatus(int id, const Task::Status& status)
{
    if (!tasks.contains(id))
        throw std::out_of_range("Failed to update task status: Invalid task id.");

    tasks.at(id).status = status;

    UpdateStorage();
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
    storage.Save(TasksData{ tasks, nextId });
}
