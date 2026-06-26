#pragma once

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

    TaskManager taskManager;
};
