#ifndef TASKMODIFY_H
#define TASKMODIFY_H

#include "TaskReader.h"
#include <string>
#include <vector>
class TaskModify
{
public:
    explicit TaskModify(const std::string &filePath);
    bool removeById(int id);

private:
    bool writeAll(const std::vector<Task> &Tasks);
    std::string filePath_;
};

#endif