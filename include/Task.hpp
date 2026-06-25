#pragma once

#include <string>

struct Task
{
    enum class Status
    {
        TODO = 0,
        IN_PROGRESS,
        DONE
    };

    explicit Task(const std::string& title, const Status& status) : title(title), status(status) {}
    explicit Task(const std::string& title) : Task(title, Status::TODO) {}

    std::string title;
    Status status;
};
