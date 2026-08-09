#include "todo.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <utility>

TodoStore::TodoStore(std::string path) : path_(std::move(path))
{
    load();
}

bool TodoStore::load()
{
    items_.clear();
    std::ifstream in(path_);
    if (!in)
        return true; // 文件不存在 → 空仓库
    std::string line;
    while (std::getline(in, line))
    {
        if (line.empty())
            continue;
        std::istringstream iss(line);
        std::string id_s, done_s, text;
        if (!std::getline(iss, id_s, '|'))
            continue;
        if (!std::getline(iss, done_s, '|'))
            continue;
        if (!std::getline(iss, text))
            text.clear();
        try
        {
            Todo t;
            t.id = std::stoi(id_s);
            t.done = (done_s == "1");
            t.text = text;
            items_.push_back(std::move(t));
        }
        catch (...)
        { /* 跳过格式错误的行 */
        }
    }
    next_id_ = 1;
    for (auto &t : items_)
        if (t.id >= next_id_)
            next_id_ = t.id + 1;
    return true;
}

bool TodoStore::save() const
{
    std::ofstream out(path_, std::ios::trunc);
    if (!out)
        return false;
    for (const auto &t : items_)
    {
        out << t.id << '|' << (t.done ? '1' : '0') << '|' << t.text << '\n';
    }
    return true;
}

int TodoStore::add(const std::string &text)
{
    Todo t;
    t.id = next_id_++;
    t.done = false;
    t.text = text;
    items_.push_back(t);
    save();
    return t.id;
}

bool TodoStore::remove(int id)
{
    auto it = std::find_if(items_.begin(), items_.end(),
                           [id](const Todo &t)
                           { return t.id == id; });
    if (it == items_.end())
        return false; // 没找到
    items_.erase(it);
    save();
    return true;
}

bool TodoStore::mark_done(int id)
{
    for (auto &t : items_)
    {
        if (t.id == id)
        {
            t.done = true;
            save();
            return true;
        }
    }
    return false;
}

void TodoStore::clear()
{
    items_.clear();
    save();
}

void TodoStore::list(std::ostream &os) const
{
    for (const auto &t : items_)
    {
        os << t.id << ' ' << (t.done ? "[x] " : "[ ] ") << t.text << '\n';
    }
}
