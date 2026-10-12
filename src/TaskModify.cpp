#include "TaskModify.h"
#include <fstream>
#include <algorithm>

TaskModify::TaskModify(const std::string &filePath)
    : filePath_(filePath) {}

bool TaskModify::removeById(int id)
{
    TaskReader reader(filePath_);
    std::vector<Task> tasks = reader.all();
    auto newEnd = std::remove_if(tasks.begin(), tasks.end(),
                                 [id](const Task &t)
                                 { return t.id == id; });
    if (newEnd == tasks.end())
        return false;
    tasks.erase(newEnd, tasks.end());
    return writeAll(tasks);
}
bool TaskModify::writeAll(const std::vector<Task> &tasks)
{
    std::ofstream out(filePath_, std::ios::trunc);
    if (!out)
        return false;
    for (const auto &t : tasks)
    {
        out << t.id << '|'
            << t.title << '|'
            << t.createdAt << '|'
            << t.co_time << std::endl;
    }
    return true;
}