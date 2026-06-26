#pragma once

#include <iostream>
#include <format>

#include "Task.hpp"

namespace Print
{
namespace Color
{
    constexpr const char* Reset  = "\033[0m";
    constexpr const char* Red    = "\033[31m";
    constexpr const char* Green  = "\033[32m";
    constexpr const char* Yellow = "\033[33m";
}

    template <typename T>
    void Info(T msg)
    {
        std::cout << Color::Green << "[Info]: " << msg << Color::Reset << std::endl;
    }

    template <typename T>
    void Warning(T msg)
    {
        std::cerr << Color::Yellow << "[Warning]: " << msg << Color::Reset << std::endl;
    }

    template <typename T>
    void Error(T msg)
    {
        std::cerr << Color::Red << "[Error]: " << msg << Color::Reset << std::endl;
    }

    template<std::ranges::input_range Range>
    void Tasks(Range&& tasks)
    {
        for (const auto& [id, task] : tasks)
        {
            std::cout << Color::Green << 
                std::format("{}: \"{}\" [{}]", id, task.title, Task::StatusToString(task.status)) 
                << Color::Reset << std::endl;
        }
    }
}
