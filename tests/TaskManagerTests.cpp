#include <gtest/gtest.h>
#include <string>

#include "TaskManager.hpp"

TEST(TaskManager, EmptyInitTest)
{
    TaskManager taskManager;

    EXPECT_EQ(taskManager.GetAllTasks().size(), 0);
}

TEST(TaskManager, AddTest)
{
    TaskManager taskManager;
    const std::string taskTitle = "Buy groceries";
    taskManager.Add(taskTitle);
    
    auto task = taskManager.GetTaskById(1);
    EXPECT_EQ(taskManager.GetAllTasks().size(), 1);
    EXPECT_EQ(task.title, taskTitle);
    EXPECT_EQ(task.status, Task::Status::TODO);
}

TEST(TaskManager, DeleteTest)
{
    TaskManager taskManager;
    const std::string taskTitle = "Buy groceries";
    taskManager.Add(taskTitle);
    taskManager.Delete(1);
    
    EXPECT_THROW(taskManager.Delete(0), std::out_of_range);
    EXPECT_THROW(taskManager.Delete(999), std::out_of_range);

    auto tasks = taskManager.GetAllTasks();
    EXPECT_EQ(tasks.size(), 0);
}

TEST(TaskManager, UpdateTest)
{
    TaskManager taskManager;
    const std::string taskTitle = "Buy groceries";
    taskManager.Add(taskTitle);

    const std::string newTaskTitle = "Buy milk and chocolate";
    EXPECT_THROW(taskManager.Update(0, newTaskTitle), std::out_of_range);
    EXPECT_THROW(taskManager.Update(999, newTaskTitle), std::out_of_range);

    taskManager.Update(1, newTaskTitle);

    auto task = taskManager.GetTaskById(1);
    EXPECT_EQ(task.title, newTaskTitle);
}

TEST(TaskManager, UpdateStatusTest)
{
    TaskManager taskManager;
    const std::string taskTitle = "Buy groceries";
    taskManager.Add(taskTitle);
    
    auto task = taskManager.GetTaskById(1);
    EXPECT_EQ(task.status, Task::Status::TODO);

    auto newStatus = Task::Status::IN_PROGRESS;

    EXPECT_THROW(taskManager.UpdateStatus(0, newStatus), std::out_of_range);
    EXPECT_THROW(taskManager.UpdateStatus(999, newStatus), std::out_of_range);

    taskManager.UpdateStatus(1, Task::Status::IN_PROGRESS);

    task = taskManager.GetTaskById(1);
    EXPECT_EQ(task.status, newStatus);
}
