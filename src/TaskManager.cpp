#include "TaskManager.hpp"

#include <algorithm>

void TaskManager::Add(const std::string& taskMsg)
{
    tasks.push_back(Task(taskMsg));
}

void TaskManager::Update(int id, const std::string& taskMsg)
{
    tasks[id - 1].title = taskMsg;
}

void TaskManager::Delete(int id)
{
    tasks.erase(tasks.begin() + id - 1);
}

void TaskManager::UpdateStatus(int id, const Task::Status& status)
{
    tasks[id].status = status;
}

std::vector<Task> TaskManager::GetAllTasks() const
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
