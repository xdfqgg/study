#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream in("sample.log");
    if (!in)
    {
        std::cerr << "open sample.log failed\n";
        return 1;
    }

    std::unordered_map<std::string, int> freq;
    std::string line;
    while (std::getline(in, line))
    {
        std::istringstream iss(line);
        std::string word;
        while (iss >> word)
        {
            ++freq[word];
        }
    }

    std::vector<std::pair<std::string, int>> items(freq.begin(), freq.end());
    std::sort(items.begin(), items.end(), [](const auto &a, const auto &b)
              { return a.second > b.second; });

    for (std::size_t i = 0; i < std::min<std::size_t>(items.size(), 10); ++i)
    {
        std::cout << items[i].first << ": " << items[i].second << '\n';
    }

    return 0;
}
