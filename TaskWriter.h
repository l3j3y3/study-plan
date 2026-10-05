#ifndef TASKWRITER_H
#define TASKWRITER_H

#include <string>

struct Task
{
    int id;
    std::string title;
    std::string createdAt;
};

class TaskWriter
{
public:
    explicit TaskWriter(const std::string &filePath);
    bool append(const Task &task) const;
    int nextId() const;
    static std::string nowString();

private:
    std::string filePath_;
};

#endif
