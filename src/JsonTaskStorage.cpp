#include "JsonTaskStorage.hpp"

#include <fstream>
#include <format>
#include <iterator>
#include <regex>

constexpr char* storage_file_name = "tasks_storage.json";

void JsonTaskStorage::Save(const std::unordered_map<int, Task>& tasks)
{
    std::ofstream file(storage_file_name);
    std::string json = "{\n\"tasks\": [\n";
    for (auto it = tasks.begin(); it != tasks.end(); ++it)
    {
        json += std::format(
R"({{
    "id": {},
    "title": "{}",
    "status": {}
}})",
            it->first,
            it->second.title,
            static_cast<int>(it->second.status)
        );

        if (std::next(it) != tasks.end())
            json += ",";

        json += "\n";
    }
    json += "]}\n";

    file << json;
}

std::unordered_map<int, Task> JsonTaskStorage::Load()
{
    std::unordered_map<int, Task> tasks;

    std::ifstream file(storage_file_name);
    if (!file)
        return tasks;

    std::string json{std::istreambuf_iterator<char>{file}, std::istreambuf_iterator<char>{}};

    std::regex taskRegex(
        R"(\{\s*\"id\"\s*:\s*(\d+)\s*,\s*\"title\"\s*:\s*\"([^\"]*)\"\s*,\s*\"status\"\s*:\s*(\d+)\s*\})"
    );

    auto begin = std::sregex_iterator(json.begin(), json.end(), taskRegex);
    auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it)
    {
        int id = std::stoi((*it)[1].str());
        std::string title = (*it)[2].str();
        int status = std::stoi((*it)[3].str());

        tasks.emplace(
            id,
            Task {
                title,
                static_cast<Task::Status>(status)
            }
        );
    }

    return tasks;
}
