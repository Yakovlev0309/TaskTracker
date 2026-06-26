#include <iostream>

#include "Command/CommandHandler.hpp"

int main(int argc, char* argv[])
{
    CommandHandler commandHandler;
    return commandHandler.HandleCommand(argc, argv);
}
