#include <gtest/gtest.h>
#include <string>

#include "Task/TaskManager.hpp"

TEST(TaskManager, EmptyInitTest)
{
    TaskManager taskManager;

    EXPECT_EQ(taskManager.GetAllTasks().size(), 0);
}

TEST(TaskManager, AddTest)
{
    TaskManager taskManager;
    const std::string taskDescription = "Buy groceries";
    const int id = taskManager.Add(taskDescription);
    
    EXPECT_EQ(id, 1);

    auto task = taskManager.GetTaskById(id);
    EXPECT_EQ(taskManager.GetAllTasks().size(), id);
    EXPECT_EQ(task.description, taskDescription);
    EXPECT_EQ(task.status, Task::Status::TODO);

    const int id2 = taskManager.Add("Another task");
    EXPECT_EQ(taskManager.GetAllTasks().size(), 2);
    EXPECT_EQ(id2, 2);
}

TEST(TaskManager, DeleteTest)
{
    TaskManager taskManager;
    const std::string taskDescription = "Buy groceries";
    const int id = taskManager.Add(taskDescription);
    taskManager.Delete(id);
    
    EXPECT_THROW(taskManager.Delete(0), std::out_of_range);
    EXPECT_THROW(taskManager.Delete(999), std::out_of_range);

    auto tasks = taskManager.GetAllTasks();
    EXPECT_EQ(tasks.size(), 0);
}

TEST(TaskManager, UpdateTest)
{
    TaskManager taskManager;
    const std::string taskDescription = "Buy groceries";
    const int id = taskManager.Add(taskDescription);

    const std::string newTaskDescription = "Buy milk and chocolate";
    EXPECT_THROW(taskManager.UpdateDescription(0, newTaskDescription), std::out_of_range);
    EXPECT_THROW(taskManager.UpdateDescription(999, newTaskDescription), std::out_of_range);

    taskManager.UpdateDescription(id, newTaskDescription);

    auto task = taskManager.GetTaskById(id);
    EXPECT_EQ(task.description, newTaskDescription);
}

TEST(TaskManager, UpdateStatusTest)
{
    TaskManager taskManager;
    const std::string taskDescription = "Buy groceries";
    const int id = taskManager.Add(taskDescription);
    
    auto task = taskManager.GetTaskById(id);
    EXPECT_EQ(task.status, Task::Status::TODO);

    auto newStatus = Task::Status::IN_PROGRESS;

    EXPECT_THROW(taskManager.UpdateStatus(0, newStatus), std::out_of_range);
    EXPECT_THROW(taskManager.UpdateStatus(999, newStatus), std::out_of_range);

    taskManager.UpdateStatus(id, Task::Status::IN_PROGRESS);

    task = taskManager.GetTaskById(id);
    EXPECT_EQ(task.status, newStatus);
}
