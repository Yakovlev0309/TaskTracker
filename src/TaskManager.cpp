#include "TaskManager.hpp"

#include <algorithm>

void TaskManager::Add(const std::string& taskMsg)
{
    tasks.push_back(Task(taskMsg));
}

void TaskManager::Update(int id, const std::string& taskMsg)
{
    if (id < 1 || id > tasks.size())
        throw std::out_of_range("Failed to update task title: Invalid task id.");

    tasks[id - 1].title = taskMsg;
}

void TaskManager::Delete(int id)
{
    if (id < 1 || id > tasks.size())
        throw std::out_of_range("Failed to delete task: Invalid task id.");

    tasks.erase(tasks.begin() + id - 1);
}

void TaskManager::UpdateStatus(int id, const Task::Status& status)
{
    if (id < 1 || id > tasks.size())
        throw std::out_of_range("Failed to update task status: Invalid task id.");

    tasks[id - 1].status = status;
}

const std::vector<Task>& TaskManager::GetAllTasks() const
{
    return tasks;
}

std::vector<Task> TaskManager::GetTasksByStatus(const Task::Status& status) const
{
    std::vector<Task> result;
    std::for_each(tasks.begin(), tasks.end(), [&status, &result](const Task& task){
        if (task.status == status)
            result.push_back(task);
    });
    return result;
}
