#include "todo.h"
#include <iostream>

void print_usage(const char *prog)
{
    std::cout << "Usage:\n"
              << "  " << prog << " add \"task description\"\n"
              << "  " << prog << " list\n"
              << "  " << prog << " done <id>\n"
              << "  " << prog << " rm <id>\n"
              << "  " << prog << " clear\n"
              << "  " << prog << " help\n";
}

int main(int argc, char **argv)
{
    TodoStore store("todo.txt"); // 创建仓库并自动 load

    if (argc < 2)
    { // 没给命令
        print_usage(argv[0]);
        return 1;
    }

    std::string cmd = argv[1]; // 取出命令

    if (cmd == "add")
    {
        if (argc < 3)
        {
            std::cerr << "add needs a task string\n";
            return 1;
        }
        std::string text = argv[2];
        // 若没加引号传了多个词，把剩余参数拼起来
        for (int i = 3; i < argc; ++i)
        {
            text += ' ';
            text += argv[i];
        }
        int id = store.add(text);
        std::cout << "Added id=" << id << "\n";
    }
    else if (cmd == "list")
    {
        store.list();
    }
    else if (cmd == "done")
    {
        if (argc < 3)
        {
            std::cerr << "done needs an id\n";
            return 1;
        }
        int id = std::stoi(argv[2]);
        if (!store.mark_done(id))
            std::cerr << "no such id\n";
    }
    else if (cmd == "rm")
    {
        if (argc < 3)
        {
            std::cerr << "rm needs an id\n";
            return 1;
        }
        int id = std::stoi(argv[2]);
        if (!store.remove(id))
            std::cerr << "no such id\n";
    }
    else if (cmd == "clear")
    {
        std::cout << "Are you sure? type yes to confirm: ";
        std::string ans;
        std::getline(std::cin, ans);
        if (ans == "yes")
            store.clear();
    }
    else if (cmd == "help")
    {
        print_usage(argv[0]);
    }
    else
    {
        std::cerr << "Unknown command\n";
        print_usage(argv[0]);
        return 1;
    }
    return 0;
}
