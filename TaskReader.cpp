#include "TaskReader.h"
#include <fstream>
#include <sstream>
#include <iostream>
TaskReader::TaskReader(const std::string &filePath)
    : filePath_(filePath) {}

bool TaskReader::parseLine(const std::string &line, Task &task)
{
    if (line.empty())
        return false;

    std::stringstream ss(line);
    std::string idStr, title, createdAt, coStr;

    if (!std::getline(ss, idStr, '|'))
        return false;
    if (!std::getline(ss, title, '|'))
        return false;
    if (!std::getline(ss, createdAt, '|'))
        return false;

    try
    {
        task.id = std::stoi(idStr);
    }
    catch (...)
    {
        return false;
    }
    task.title = title;
    task.createdAt = createdAt;
    if (std::getline(ss, coStr, '|') && !coStr.empty())
    {
        try
        {
            task.co_time = std::stod(coStr);
        }
        catch (...)
        {
            task.co_time = 0.0;
        }
    }
    else
    {
        task.co_time = 0.0;
    }
    return true;
}

bool TaskReader::findById(int id, Task &out) const
{
    for (const auto &t : all())
    {
        if (t.id == id)
        {
            out = t;
            return true;
        }
    }
    return false;
}

std::vector<Task> TaskReader::findByTitle(const std::string &keyword) const
{
    std::vector<Task> result;
    for (const auto &t : all())
    {
        if (t.title.find(keyword) != std::string::npos)
            return result;
    }
    return result;
}
