#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

struct LogEntry
{
    std::string ip;
    std::string method;
    std::string path;
    int status = 0;
};

bool parse_log_line(const std::string &line, LogEntry &out)
{
    // 1. 取 IP：开头到第一个空格
    size_t first_space = line.find(' ');
    if (first_space == std::string::npos)
        return false;
    out.ip = line.substr(0, first_space);

    // 2. 取请求行：双引号内的内容
    size_t q1 = line.find('"');
    size_t q2 = line.find('"', q1 + 1);
    if (q1 == std::string::npos || q2 == std::string::npos)
        return false;

    std::string request = line.substr(q1 + 1, q2 - q1 - 1);

    // 3. 解析 request = "METHOD PATH HTTP/1.1"
    size_t method_end = request.find(' ');
    if (method_end == std::string::npos)
        return false;
    out.method = request.substr(0, method_end);

    size_t path_start = method_end + 1;
    size_t path_end = request.find(' ', path_start);
    if (path_end == std::string::npos)
        return false;
    out.path = request.substr(path_start, path_end - path_start);

    // 4. 解析状态码：从请求结束的右引号后面开始，跳过空格，然后取连续数字
    size_t after_request = q2 + 1;
    while (after_request < line.size() && std::isspace(static_cast<unsigned char>(line[after_request])))
    {
        ++after_request;
    }

    size_t status_begin = after_request;
    size_t status_end = status_begin;
    while (status_end < line.size() && std::isdigit(static_cast<unsigned char>(line[status_end])))
    {
        ++status_end;
    }

    if (status_begin == status_end)
        return false;

    std::string status_str = line.substr(status_begin, status_end - status_begin);
    out.status = std::stoi(status_str);

    return true;
}

int main()
{
    std::string line = "127.0.0.1 - - [12/Mar/2026:18:25:11 +0000] \"GET /index.html HTTP/1.1\" 200 1024";
    LogEntry entry;
    if (parse_log_line(line, entry))
    {
        std::cout << entry.ip << '\n';
        std::cout << entry.method << '\n';
        std::cout << entry.path << '\n';
        std::cout << entry.status << '\n';
    }
}