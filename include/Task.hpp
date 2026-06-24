#pragma once

#include <string>

struct Task
{
    enum class Status
    {
        TODO,
        IN_PROGRESS,
        DONE
    };

    explicit Task(const std::string& title) : title(title) {}

    std::string title;
    Status status = Status::TODO;
};
