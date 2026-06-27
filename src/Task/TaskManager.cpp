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
    if (!tasks.contains(id))
        throw TaskNotFoundException(id);

    tasks.at(id).description = taskMsg;

    UpdateStorage();
}

void TaskManager::UpdateStatus(int id, const Task::Status& status)
{
    if (!tasks.contains(id))
        throw TaskNotFoundException(id);

    tasks.at(id).status = status;

    UpdateStorage();
}

Task TaskManager::GetTaskById(int id) const
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
