#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>
#include <cctype>

struct LogEntry
{
    std::string ip;
    std::string datetime;
    std::string method;
    std::string path;
    int status = 0;
    int size = 0;
};

namespace {
static size_t skip_ws(const std::string &s, size_t pos)
{
    while (pos < s.size() && std::isspace(static_cast<unsigned char>(s[pos])))
        ++pos;
    return pos;
}

static std::pair<size_t, size_t> next_token(const std::string &s, size_t pos)
{
    pos = skip_ws(s, pos);
    size_t begin = pos;
    while (pos < s.size() && !std::isspace(static_cast<unsigned char>(s[pos])))
        ++pos;
    return {begin, pos};
}
}

// 函数签名和原来完全一样，外部调用无需改动
bool parse_log_line(const std::string &line, LogEntry &out)
{
    out = {};
    size_t pos = 0;
    std::pair<size_t, size_t> tok;

    // 1. ip
    tok = next_token(line, pos);
    if (tok.first == std::string::npos || tok.first == tok.second)
        return false;
    out.ip = line.substr(tok.first, tok.second - tok.first);
    pos = tok.second;

    // 跳过两个 "-"
    tok = next_token(line, pos);
    if (tok.first == std::string::npos) return false;
    pos = tok.second;

    tok = next_token(line, pos);
    if (tok.first == std::string::npos) return false;
    pos = tok.second;

    // 2. [datetime]
    size_t bracket_open = line.find('[', pos);
    if (bracket_open == std::string::npos) return false;
    size_t bracket_close = line.find(']', bracket_open + 1);
    if (bracket_close == std::string::npos) return false;
    out.datetime = line.substr(bracket_open + 1, bracket_close - bracket_open - 1);
    pos = bracket_close + 1;

    // 3. "METHOD PATH HTTP/xxx"
    size_t q1 = line.find('"', pos);
    if (q1 == std::string::npos) return false;
    size_t q2 = line.find('"', q1 + 1);
    if (q2 == std::string::npos) return false;

    std::string req = line.substr(q1 + 1, q2 - q1 - 1);
    size_t rpos = 0;
    auto req_t1 = next_token(req, rpos);
    if (req_t1.first == std::string::npos) return false;
    out.method = req.substr(req_t1.first, req_t1.second - req_t1.first);
    rpos = req_t1.second;

    auto req_t2 = next_token(req, rpos);
    if (req_t2.first == std::string::npos) return false;
    out.path = req.substr(req_t2.first, req_t2.second - req_t2.first);

    pos = q2 + 1;

    // 4. status
    tok = next_token(line, pos);
    if (tok.first == std::string::npos) return false;
    try
    {
        out.status = std::stoi(line.substr(tok.first, tok.second - tok.first));
    }
    catch (...)
    {
        return false;
    }
    pos = tok.second;

    // 5. size，处理 "-"
    tok = next_token(line, pos);
    if (tok.first == std::string::npos) return false;
    std::string size_str = line.substr(tok.first, tok.second - tok.first);
    if (size_str == "-")
    {
        out.size = 0LL;
    }
    else
    {
        try
        {
            out.size = std::stoll(size_str);
        }
        catch (...)
        {
            return false;
        }
    }

    return true;
}

template <typename Map>
std::vector<std::pair<typename Map::key_type, typename Map::mapped_type>>
top_n(const Map &m, std::size_t N)
{
    using Pair = std::pair<typename Map::key_type, typename Map::mapped_type>;
    std::vector<Pair> items;
    items.reserve(m.size());

    for (const auto &kv : m)
    {
        items.emplace_back(kv.first, kv.second);
    }

    if (items.size() <= N)
    {
        std::sort(items.begin(), items.end(),
                  [](const Pair &a, const Pair &b)
                  {
                      return a.second > b.second;
                  });
        return items;
    }

    std::nth_element(items.begin(), items.begin() + static_cast<std::ptrdiff_t>(N), items.end(),
                     [](const Pair &a, const Pair &b)
                     {
                         return a.second > b.second;
                     });
    items.resize(N);
    std::sort(items.begin(), items.end(),
              [](const Pair &a, const Pair &b)
              {
                  return a.second > b.second;
              });
    return items;
}

void print_usage(const char *program)
{
    std::cout << "Usage: " << program << " [--file path] [--top N]\n";
    std::cout << "Example: " << program << " sample.log --top 5\n";
}

int main(int argc, char **argv)
{
    std::string file = "sample.log";
    std::size_t top = 10;

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arg == "--help" || arg == "-h")
        {
            print_usage(argv[0]);
            return 0;
        }

        if (arg == "--top" && i + 1 < argc)
        {
            top = static_cast<std::size_t>(std::stoul(argv[++i]));
        }
        else if (arg == "--file" && i + 1 < argc)
        {
            file = argv[++i];
        }
        else if (arg.rfind("--file=", 0) == 0)
        {
            file = arg.substr(7);
        }
        else if (i == 1 && arg != "--top")
        {
            file = arg;
        }
    }

    if (!std::filesystem::exists(file))
    {
        std::cerr << "file not found: " << file << '\n';
        return 1;
    }

    std::ifstream input(file);
    if (!input)
    {
        std::cerr << "open failed: " << file << '\n';
        return 1;
    }

    std::unordered_map<std::string, int> path_count;
    std::unordered_map<std::string, int> ip_count;
    std::unordered_map<int, int> status_count;

    std::size_t total = 0;
    std::size_t parsed = 0;
    std::size_t failed = 0;

    std::string line;
    while (std::getline(input, line))
    {
        ++total;
        LogEntry entry;
        if (!parse_log_line(line, entry))
        {
            ++failed;
            continue;
        }

        ++parsed;
        ++path_count[entry.path];
        ++ip_count[entry.ip];
        ++status_count[entry.status];
    }

    std::cout << "total lines=" << total
              << " parsed=" << parsed
              << " failed=" << failed << "\n\n";

    auto top_paths = top_n(path_count, top);
    std::cout << "Top " << std::min(top, top_paths.size()) << " paths:\n";
    for (const auto &[path, count] : top_paths)
    {
        std::cout << count << "\t" << path << '\n';
    }

    auto top_ips = top_n(ip_count, top);
    std::cout << "\nTop " << std::min(top, top_ips.size()) << " IPs:\n";
    for (const auto &[ip, count] : top_ips)
    {
        std::cout << count << "\t" << ip << '\n';
    }

    std::vector<std::pair<int, int>> status_pairs(status_count.begin(), status_count.end());
    std::sort(status_pairs.begin(), status_pairs.end(),
              [](const auto &a, const auto &b)
              {
                  return a.first < b.first;
              });

    std::cout << "\nStatus codes:\n";
    for (const auto &[status, count] : status_pairs)
    {
        std::cout << status << "\t" << count << '\n';
    }

    return 0;
}
