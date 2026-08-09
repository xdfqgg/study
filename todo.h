#pragma once
#include <string>
#include <vector>
#include <iostream>

struct Todo
{
    int id;
    bool done;
    std::string text;
    /* data */
};

class TodoStore
{
    std::string path_;
    int next_id_ = 1;
    std::vector<Todo> items_;

public:
    explicit TodoStore(std::string path);
    bool load();
    bool save() const;
    int add(const std::string &text);
    bool remove(int id);
    bool mark_done(int id);
    void clear();
    void list(std::ostream &os = std::cout) const;
};