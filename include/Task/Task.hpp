#pragma once

#include <string>
#include <chrono>

struct Task
{
    enum class Status
    {
        TODO = 0,
        IN_PROGRESS,
        DONE
    };

    explicit Task(const std::string& description, const Status& status = Status::TODO)
        : description(description), status(status)
    {
    }

    static constexpr std::string_view StatusToString(const Status& status)
    {
        switch (status)
        {
        case Status::TODO:
            return "todo";
        case Status::IN_PROGRESS:
            return "in progress";
        case Status::DONE:
            return "done";
        }

        return "unknown";
    }

    std::string description;
    Status status;
    std::chrono::system_clock::time_point createdAt;
    std::chrono::system_clock::time_point updatedAt;
};
