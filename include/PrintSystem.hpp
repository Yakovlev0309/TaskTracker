#pragma once

#include <iostream>
#include <format>

#include "Task.hpp"

namespace Print
{
    template <typename T>
    void Info(T msg)
    {
        std::cout << "[Info]: " << msg << std::endl;
    }

    template <typename T>
    void Error(T msg)
    {
        std::cerr << "[Error]: " << msg << std::endl;
    }

    template<std::ranges::input_range Range>
    void Tasks(Range&& tasks)
    {
        for (const auto& [id, task] : tasks)
        {
            std::cout << std::format("{}: \"{}\" [{}]", id, task.title, Task::StatusToString(task.status)) << std::endl;
        }
    }
}
