#include <iostream>
#include <string>

// 日志级别：DEBUG=0, INFO=1, WARN=2, ERROR=3（自动编号）
enum class Level { DEBUG, INFO, WARN, ERROR };

struct Logger {
    Level level = Level::DEBUG;          // 当前"门槛"：低于它的日志不输出

    void log(Level lv, const std::string& msg) {
        if (lv < level) return;          // ★ 级别不够 → 直接跳过（连格式化都不做）
        std::cerr << to_string(lv) << ": " << msg << '\n';
    }

    static std::string to_string(Level lv) {   // 把级别转成字符串
        switch (lv) {
            case Level::DEBUG: return "DEBUG";
            case Level::INFO:  return "INFO";
            case Level::WARN:  return "WARN";
            default:           return "ERROR";
        }
    }
};

int main() {
    Logger lg;
    lg.level = Level::INFO;               // 把门槛提高到 INFO
    lg.log(Level::DEBUG, "this is debug");// 会被跳过
    lg.log(Level::INFO,  "started");
    lg.log(Level::ERROR, "fatal");
    return 0;
}