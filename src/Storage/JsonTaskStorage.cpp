#include "Storage/JsonTaskStorage.hpp"

#include <fstream>
#include <format>
#include <iterator>
#include <regex>

constexpr const char* storage_file_name = "tasks_storage.json";

void JsonTaskStorage::Save(const TasksData& data)
{
    std::ofstream file(storage_file_name);
    std::string json = "{\n\"tasks\": [\n";
    for (auto it = data.tasks.begin(); it != data.tasks.end(); ++it)
    {
        json += std::format(
R"({{
    "id": {},
    "description": "{}",
    "status": {}
}})",
            it->first,
            it->second.description,
            static_cast<int>(it->second.status)
        );

        if (std::next(it) != data.tasks.end())
            json += ",\n";
    }
    json += "\n],\n\"next_id\": " + std::to_string(data.nextId) + "\n}\n";

    file << json;
}

TasksData JsonTaskStorage::Load()
{
    std::unordered_map<int, Task> tasks;

    std::ifstream file(storage_file_name);
    if (!file)
        return {tasks, -1};

    std::string json{std::istreambuf_iterator<char>{file}, std::istreambuf_iterator<char>{}};

    std::regex taskRegex(
        R"(\{\s*\"id\"\s*:\s*(\d+)\s*,\s*\"description\"\s*:\s*\"([^\"]*)\"\s*,\s*\"status\"\s*:\s*(\d+)\s*\})"
    );

    auto begin = std::sregex_iterator(json.begin(), json.end(), taskRegex);
    auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it)
    {
        int id = std::stoi((*it)[1].str());
        std::string description = (*it)[2].str();
        int status = std::stoi((*it)[3].str());

        tasks.emplace(
            id,
            Task {
                description,
                static_cast<Task::Status>(status)
            }
        );
    }

    int nextId = -1;

    std::regex nextIdRegex(
        R"("next_id"\s*:\s*(\d+))"
    );

    std::smatch match;
    if (std::regex_search(json, match, nextIdRegex))
        nextId = std::stoi(match[1].str());

    return TasksData{ std::move(tasks), nextId };
}
