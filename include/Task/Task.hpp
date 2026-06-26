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

    explicit Task(const std::string& title, const Status& status = Status::TODO)
        : title(title), status(status)
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

    std::string title;
    Status status;
};
