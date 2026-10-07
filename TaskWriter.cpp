#include "TaskWriter.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
#include <iomanip>

TaskWriter::TaskWriter(const std::string &filePath)
    : filePath_(filePath) {}

bool TaskWriter::append(const Task &task) const
{
    std::ofstream out(filePath_, std::ios::app);
    if (!out)
    {
        std::cerr << "无法打开文件" << filePath_ << std::endl;
        return false;
    }
    out << task.id << "|"
        << task.title << "|"
        << task.createdAt << "|"
        << task.co_time << std::endl;
    return true;
}

int TaskWriter::nextId() const
{
    std::ifstream in(filePath_);
    if (!in)
        return 1;
    int maxId = 0;
    std::string line;
    while (std::getline(in, line))
    {
        if (line.empty())
            continue;
        std::stringstream ss(line);
        std::string idstr;
        std::getline(ss, idstr, '|');
        try
        {
            int id = std::stoi(idstr);
            if (id > maxId)
                maxId = id;
        }
        catch (...)
        {
        }
    }
    return maxId + 1;
}

std::string TaskWriter::nowString()
{
    std::time_t t = std::time(nullptr);
    std::tm *tm = std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(tm, "%Y-%m-%d %H:%M");
    return oss.str();
}
