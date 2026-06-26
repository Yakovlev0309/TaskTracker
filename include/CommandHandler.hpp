#pragma once

#include <iostream>

#include "TaskManager.hpp"

class CommandHandler
{
public:
    int HandleCommand(int argc, char* argv[]);

private:
    int Add(int argc, char* argv[]);
    int Update(int argc, char* argv[]);
    int Delete(int argc, char* argv[]);
    int Mark(int argc, char* argv[]);
    int List(int argc, char* argv[]);

    template<std::ranges::input_range Range>
    void listTasks(Range&& tasks)
    {
        for (const auto& [id, task] : tasks)
        {
            std::cout << id << ": " << task.title << "\n";
        }
    }

    TaskManager taskManager;
};
