#ifndef TASKREADER_H
#define TASKREADER_H

#include "TaskWriter.h"
#include <string>
#include <vector>

class TaskReader
{
public:
    explicit TaskReader(const std::string &filePath);
    std::vector<Task> all() const;
    bool findById(int id, Task &out) const;
    std::vector<Task> findByTitle(const std::string &keyword) const;

private:
    static bool parseLine(const std::string &Line, Task &task);

    std::string filePath_;
};

#endif