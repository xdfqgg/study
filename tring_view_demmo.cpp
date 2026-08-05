#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <sstream>
#include <cctype>
#include <chrono>

std::vector<std::string> spilt_copy(const std::string &s)
{
    std::vector<std::string> result;
    std::istringstream iss(s);
    std::string word;
    while (iss >> word)
    {
        result.push_back(word);
    }
    return result;
}

std::vector<std::string_view> split_view(std::string_view s)
{
    std::vector<std::string_view> result;
    size_t start = 0;
    while (start < s.size())
    {
        // 1. 跳过开头的空白
        while (start < s.size() && std::isspace(s[start]))
            ++start;
        if (start >= s.size())
            break; // 只剩空白了，结束

        // 2. 找到单词的结尾
        size_t end = start;
        while (end < s.size() && !std::isspace(s[end]))
            ++end;

        // 3. 切出 view（不拷贝！只是指过去）
        result.push_back(s.substr(start, end - start));

        start = end; // 从单词末尾继续
    }
    return result;
}
int main()
{
    std::string text;
    std::getline(std::cin, text);

    // 用拷贝版拆分
    auto start = std::chrono::steady_clock::now();
    auto copy_words = spilt_copy(text);
    std::cout << "split_copy: ";
    for (const auto &w : copy_words)
        std::cout << "[" << w << "] ";
    std::cout << "\n";
    auto end = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "split_copy time: " << ms << " ms\n";

    // 用 view 版拆分
    auto start_view = std::chrono::steady_clock::now();
    auto view_words = split_view(text);
    std::cout << "split_view: ";
    for (std::string_view w : view_words)
        std::cout << "[" << w << "] ";
    std::cout << "\n";
    auto end_view = std::chrono::steady_clock::now();
    auto ms_view = std::chrono::duration_cast<std::chrono::milliseconds>(end_view - start_view).count();
    std::cout << "split_view time: " << ms_view << " ms\n";

    // 加到 main 末尾测试：
    std::string demo = "hello world";
    auto views = split_view(demo); // views[0] 指向 demo 里的 "hello"
    auto copy = spilt_copy(demo);  // copy[0] 是新拷贝的 "hello"
    demo[0] = 'H';                 // 把原字符串改成 "Hello world"

    std::cout << "修改后 views[0] = " << views[0] << "\n";         // 会输出 "Hello"！
    std::cout << "修改后 copy  = " << spilt_copy(demo)[0] << "\n"; // 输出 "Hello"（新拷贝，跟着新值）ghifi
    std::cout << "修改前 copy[0] = " << copy[0] << "\n";           // 输出 "hello"（旧拷贝，没变）

    return 0;
}