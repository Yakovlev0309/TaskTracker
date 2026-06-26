#include "CommandHandler.hpp"

int CommandHandler::HandleCommand(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "[Error] " << "No command provided.\n";
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
        std::cerr << "[Error] " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

int CommandHandler::Add(int argc, char* argv[])
{
    if (argc < 3)
        throw std::runtime_error("Usage: TaskTracker add \"task title\"");

    const std::string title = argv[2];
    const int id = taskManager.Add(title);

    std::cout << "Task added successfully (ID: " << id << ")\n";

    return EXIT_SUCCESS;
}

int CommandHandler::Update(int argc, char* argv[])
{
    if (argc < 4)
        throw std::runtime_error("Usage: TaskTracker update N \"new title\"");

    const int id = std::stoi(argv[2]);
    const std::string newTitle = argv[3];

    taskManager.UpdateTitle(id, newTitle);

    return EXIT_SUCCESS;
}

int CommandHandler::Delete(int argc, char* argv[])
{
    if (argc < 3)
        throw std::runtime_error("Usage: TaskTracker delete N");

    const int id = std::stoi(argv[2]);
    taskManager.Delete(id);

    return EXIT_SUCCESS;
}

int CommandHandler::Mark(int argc, char* argv[])
{
    const std::string command = argv[1];

    if (command == "mark-in-progress")
    {
        if (argc < 3)
            throw std::runtime_error("Usage: TaskTracker mark-in-progress N");

        int id = std::stoi(argv[2]);
        taskManager.UpdateStatus(id, Task::Status::IN_PROGRESS);
    }
    else if (command == "mark-done")
    {
        if (argc < 3)
            throw std::runtime_error("Usage: TaskTracker mark-done N");

        int id = std::stoi(argv[2]);
        taskManager.UpdateStatus(id, Task::Status::DONE);
    }
    else
        throw std::runtime_error("Usage: TaskTracker mark-in-progress/mark-done N");

    return EXIT_SUCCESS;
}

int CommandHandler::List(int argc, char* argv[])
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
            listTasks(taskManager.GetTasksByStatus(Task::Status::DONE));
        else if (filter == "in-progress")
            listTasks(taskManager.GetTasksByStatus(Task::Status::IN_PROGRESS));
        else if (filter == "todo")
            listTasks(taskManager.GetTasksByStatus(Task::Status::TODO));
        else
           throw std::runtime_error("Usage: TaskTracker list todo/done/in-progress");
    }

    return EXIT_SUCCESS;
}
