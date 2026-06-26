#include "CommandHandler.hpp"
#include "PrintSystem.hpp"

#include <format>

int CommandHandler::HandleCommand(int argc, char* argv[])
{
    if (argc < 2)
    {
        Print::Error("No command provided.");
        return EXIT_FAILURE;
    }

    const std::string command = argv[1];

    try
    {
        if (command == "add")
            return Add(argc, argv);
        else if (command == "update")
            return Update(argc, argv);
        else if (command == "delete")
            return Delete(argc, argv);
        else if (command == "mark-in-progress" || command == "mark-done")
            return Mark(argc, argv);
        else if (command == "list")
            return List(argc, argv);
        else
            throw std::runtime_error("Unknown command");
    }
    catch (const std::exception& e)
    {
        Print::Error(e.what());
        return EXIT_FAILURE;
    }
}

int CommandHandler::Add(int argc, char* argv[])
{
    if (argc < 3)
        throw std::runtime_error("Usage: TaskTracker add \"task title\"");

    const std::string title = argv[2];
    const int id = taskManager.Add(title);

    Print::Info(std::format("Task added successfully (ID: {})", id));

    return EXIT_SUCCESS;
}

int CommandHandler::Update(int argc, char* argv[])
{
    if (argc < 4)
        throw std::runtime_error("Usage: TaskTracker update N \"new title\"");

    const int id = std::stoi(argv[2]);
    const std::string newTitle = argv[3];

    taskManager.UpdateTitle(id, newTitle);

    Print::Info(std::format("Task updated successfully (ID: {})", id));

    return EXIT_SUCCESS;
}

int CommandHandler::Delete(int argc, char* argv[])
{
    if (argc < 3)
        throw std::runtime_error("Usage: TaskTracker delete N");

    const int id = std::stoi(argv[2]);
    taskManager.Delete(id);

    Print::Info(std::format("Task deleted successfully (ID: {})", id));

    return EXIT_SUCCESS;
}

int CommandHandler::Mark(int argc, char* argv[])
{
    if (argc < 3)
        throw std::runtime_error("Usage: TaskTracker mark-in-progress/mark-done N");

    const int id = std::stoi(argv[2]);

    const std::string command = argv[1];

    if (command == "mark-in-progress")
        taskManager.UpdateStatus(id, Task::Status::IN_PROGRESS);
    else if (command == "mark-done")
        taskManager.UpdateStatus(id, Task::Status::DONE);
    else
        throw std::runtime_error("Usage: TaskTracker mark-in-progress/mark-done N");

    Print::Info(std::format("Task status changed successfully (ID: {})", id));

    return EXIT_SUCCESS;
}

int CommandHandler::List(int argc, char* argv[])
{
    if (argc == 2)
    {
        const auto& tasks = taskManager.GetAllTasks();
        Print::Tasks(tasks);
    }
    else
    {
        std::vector<std::pair<int, Task>> tasks;
        std::string filter = argv[2];

        if (filter == "done")
            Print::Tasks(taskManager.GetTasksByStatus(Task::Status::DONE));
        else if (filter == "in-progress")
            Print::Tasks(taskManager.GetTasksByStatus(Task::Status::IN_PROGRESS));
        else if (filter == "todo")
            Print::Tasks(taskManager.GetTasksByStatus(Task::Status::TODO));
        else
            throw std::runtime_error("Usage: TaskTracker list todo/done/in-progress");
    }

    return EXIT_SUCCESS;
}
