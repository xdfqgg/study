#include <bits/stdc++.h>

int main () {
    std::string line;
    std::getline(std::cin, line);

    std::unordered_map<std::string,int> count;
    std::istringstream iss(line);
    std::string word;
    while (iss >> word ) {
        count[word]++;
    }
    std::vector<std::pair<std::string,int>> items(count.begin(),count.end());
    std::sort(items.begin(), items.end(), [](const auto&a, const auto&b){
        if (a.second != b.second) {
            return a.second > b.second;
        }
        return a.first < b.first;
    });
    int limit = std::min(5, (int)items.size());
    for (int i = 0; i < limit; ++i) {
        std::cout << items[i].first << ": " << items[i].second << std::endl;
    }
 
}