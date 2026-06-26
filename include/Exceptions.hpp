#pragma once

#include <stdexcept>

class TaskException : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

class TaskNotFoundException : public TaskException
{
public:
    explicit TaskNotFoundException(int id)
        : TaskException("Task with ID " + std::to_string(id) + " not found")
    {}
};

class InvalidCommandException : public TaskException
{
public:
    explicit InvalidCommandException(std::string_view cmd)
        : TaskException("Unknown command: " + std::string(cmd))
    {}
};

class InvalidArgumentException : public TaskException
{
public:
    explicit InvalidArgumentException(std::string_view msg)
        : TaskException(std::string(msg))
    {}
};
