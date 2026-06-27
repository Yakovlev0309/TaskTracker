#include "Task/TaskManager.hpp"
#include "Storage/TasksData.hpp"
#include "Exception/Exceptions.hpp"

#include <algorithm>

TaskManager::TaskManager()
{
    TasksData data = storage.Load();
    tasks = std::move(data.tasks);
    nextId = data.nextId;
}

int TaskManager::Add(const std::string& taskMsg)
{
    tasks.emplace(nextId, Task(taskMsg));
    
    Task& task = GetTaskById(nextId);
    task.createdAt = std::chrono::system_clock::now();
    task.updatedAt = task.createdAt;

    ++nextId;
    UpdateStorage();

    return nextId - 1;
}

void TaskManager::Delete(int id)
{
    if (!tasks.contains(id))
        throw TaskNotFoundException(id);

    tasks.erase(id);

    UpdateStorage();
}

void TaskManager::UpdateDescription(int id, const std::string& taskMsg)
{
    Task& task = GetTaskById(id);

    task.description = taskMsg;
    task.updatedAt = std::chrono::system_clock::now();

    UpdateStorage();
}

void TaskManager::UpdateStatus(int id, const Task::Status& status)
{
    Task& task = GetTaskById(id);

    task.status = status;
    task.updatedAt = std::chrono::system_clock::now();

    UpdateStorage();
}

Task& TaskManager::GetTaskById(int id)
{
    auto it = tasks.find(id);

    if (it == tasks.end())
        throw TaskNotFoundException(id);

    return it->second;
}

void TaskManager::UpdateStorage()
{
    storage.Save(TasksData{ tasks, nextId });
}
