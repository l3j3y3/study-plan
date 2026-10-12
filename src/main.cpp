#include <windows.h>
#include "TaskWriter.h"
#include "TaskReader.h"
#include "TaskModify.h"
#include "Stopwatch.h"
#include <iostream>
#include <string>

// 打印一条任务的辅助函数
static void printTask(const Task &t)
{
    std::cout << "#" << t.id
              << "  " << t.title
              << "  " << t.createdAt
              << "  用时 " << t.co_time << " 秒\n";
}

// 计时学习并保存
static void doStudy(TaskWriter &writer)
{
    std::cout << "今天要学习什么？";
    std::string title;
    std::getline(std::cin, title);

    if (title.empty())
    {
        std::cout << "标题为空，已取消。\n";
        return;
    }

    Stopwatch sw;
    sw.start();
    std::cout << "开始计时，学习结束后按回车停止...\n";
    std::cin.get();
    sw.stop();

    double seconds = sw.elapsed_seconds();

    Task task;
    task.id = writer.nextId();
    task.title = title;
    task.createdAt = TaskWriter::nowString();
    task.co_time = seconds;

    if (writer.append(task))
    {
        std::cout << "已保存任务 #" << task.id
                  << "：" << task.title
                  << "，用时 " << seconds << " 秒\n";
    }
}

// 列出全部
static void doList(TaskReader &reader)
{
    auto all = reader.all();
    if (all.empty())
    {
        std::cout << "还没有任何任务。\n";
        return;
    }

    std::cout << "--- 共 " << all.size() << " 条任务 ---\n";
    for (const auto &t : all)
        printTask(t);
}

// 按 id 查
static void doFindById(TaskReader &reader)
{
    std::cout << "请输入任务 id：";
    std::string line;
    std::getline(std::cin, line);

    int id = 0;
    try
    {
        id = std::stoi(line);
    }
    catch (...)
    {
        std::cout << "id 不合法。\n";
        return;
    }

    Task found;
    if (reader.findById(id, found))
    {
        std::cout << "找到：\n";
        printTask(found);
    }
    else
    {
        std::cout << "没有 id 为 " << id << " 的任务。\n";
    }
}

// 按 id 删除
static void doRemoveById(TaskModify &mod)
{
    std::cout << "请输入要删除的任务 id：";
    std::string line;
    std::getline(std::cin, line);

    int id = 0;
    try
    {
        id = std::stoi(line);
    }
    catch (...)
    {
        std::cout << "id 不合法。\n";
        return;
    }

    if (mod.removeById(id))
        std::cout << "已删除任务 #" << id << "。\n";
    else
        std::cout << "没有 id 为 " << id << " 的任务。\n";
}

// 按标题关键字查
static void doFindByTitle(TaskReader &reader)
{
    std::cout << "请输入标题关键字：";
    std::string key;
    std::getline(std::cin, key);

    if (key.empty())
    {
        std::cout << "关键字为空，已取消。\n";
        return;
    }

    auto hits = reader.findByTitle(key);
    if (hits.empty())
    {
        std::cout << "没有匹配 \"" << key << "\" 的任务。\n";
        return;
    }

    std::cout << "匹配到 " << hits.size() << " 条：\n";
    for (const auto &t : hits)
        printTask(t);
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    TaskWriter writer("tasks.txt");
    TaskReader reader("tasks.txt");
    TaskModify mod("tasks.txt");

    while (true)
    {
        std::cout << "\n===== 学习计时器 =====\n"
                  << "1. 开始学习（计时并保存）\n"
                  << "2. 列出全部任务\n"
                  << "3. 按 id 查找\n"
                  << "4. 按标题查找\n"
                  << "5. 删除任务（按 id）\n"
                  << "0. 退出\n"
                  << "请选择：";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1")
            doStudy(writer);
        else if (choice == "2")
            doList(reader);
        else if (choice == "3")
            doFindById(reader);
        else if (choice == "4")
            doFindByTitle(reader);
        else if (choice == "5")
            doRemoveById(mod);
        else if (choice == "0")
        {
            std::cout << "再见！\n";
            break;
        }
        else
            std::cout << "无效选项，请重新输入。\n";
    }

    return 0;
}