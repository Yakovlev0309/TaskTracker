#include <iostream>

#include "TaskManager.hpp"

void listTasks(const std::unordered_map<int, Task>& tasks)
{
    for (const auto& task : tasks)
        std::cout << task.first << ": " << task.second.title << "\n";
}

void listTasks(const std::vector<std::pair<int, Task>>& tasks)
{
    for (const auto& task : tasks)
        std::cout << task.first << ": " << task.second.title << "\n";
}

int main(int argc, char* argv[])
{
    TaskManager taskManager;

    if (argc < 2)
    {
        std::cout << "No command provided.\n";
        return 1;
    }

    const std::string command = argv[1];

    if (command == "add")
    {
        if (argc < 3)
        {
            std::cout << "Usage: task-cli add \"task title\"\n";
            return 1;
        }

        const std::string title = argv[2];
        const int id = taskManager.Add(title);

        std::cout << "Task added successfully (ID: " << id << ")\n";
    }
    else if (command == "update")
    {
        if (argc < 4)
        {
            std::cout << "Usage: task-cli update N \"new title\"\n";
            return 1;
        }

        const int id = std::stoi(argv[2]);
        const std::string newTitle = argv[3];

        taskManager.UpdateTitle(id, newTitle);
    }
    else if (command == "delete")
    {
        if (argc < 3)
        {
            std::cout << "Usage: task-cli delete N\n";
            return 1;
        }

        const int id = std::stoi(argv[2]);
        taskManager.Delete(id);
    }
    else if (command == "mark-in-progress")
    {
        if (argc < 3)
        {
            std::cout << "Usage: task-cli mark-in-progress N \"new title\"\n";
            return 1;
        }

        int id = std::stoi(argv[2]);
        taskManager.UpdateStatus(id, Task::Status::IN_PROGRESS);
    }
    else if (command == "mark-done")
    {
        if (argc < 3)
        {
            std::cout << "Usage: task-cli mark-done N \"new title\"\n";
            return 1;
        }

        int id = std::stoi(argv[2]);
        taskManager.UpdateStatus(id, Task::Status::DONE);
    }
    else if (command == "list")
    {
        if (argc == 2)
        {
            const auto& tasks = taskManager.GetAllTasks();
            listTasks(tasks);
        }
        else
        {
            std::vector<std::pair<int, Task>> tasks;
            std::string filter = argv[2];

            if (filter == "done")
            {
                tasks = taskManager.GetTasksByStatus(Task::Status::DONE);

            }
            else if (filter == "in-progress")
            {
                tasks = taskManager.GetTasksByStatus(Task::Status::IN_PROGRESS);
            }
            else
            {
                tasks = taskManager.GetTasksByStatus(Task::Status::TODO);
            }

            listTasks(tasks);
        }
    }

    return 0;
}
