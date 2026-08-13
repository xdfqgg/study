#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <regex>
#include <string>
#include <vector>

// 生成一个随机字符串（长度 len，字符从字母数字里抽）
std::string random_word(std::mt19937_64& rng, int len) {
    static const char alphanum[] =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";
    // 分布范围 0 ~ size-1（别越界！）
    std::uniform_int_distribution<int> dist(0, (int)std::size(alphanum) - 2);
    std::string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) s.push_back(alphanum[dist(rng)]);
    return s;
}


int main() {
    const int N = 200000;                       // 生成多少词
    std::mt19937_64 rng((std::random_device())());  // 引擎 + 真随机种子
    std::uniform_int_distribution<int> len_dist(3, 12);  // 每个词长度 3~12

    // ① 生成 N 个随机词
    std::vector<std::string> words;
    words.reserve(N);
    for (int i = 0; i < N; ++i)
        words.push_back(random_word(rng, len_dist(rng)));

    // ② 正则规则：3~8 个字母，结尾可选 1 位数字
    std::regex re(R"([A-Za-z]{3,8}\d?)");

    // ③ 掐表：开始计时
    auto t0 = std::chrono::steady_clock::now();
    size_t matched = 0;
    for (auto& w : words) {
        if (std::regex_match(w, re)) ++matched;
    }
    // ④ 掐表：结束计时，算差值
    auto t1 = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
    std::cout << "matched=" << matched << " ms=" << ms << '\n';
    return 0;
}