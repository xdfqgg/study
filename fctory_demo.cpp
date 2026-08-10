#include <iostream>
#include <memory>
#include <string>

// 接口：规定"所有 Logger 都必须能 log"
class Logger {
public:
    virtual ~Logger() = default;          // 虚析构：必须！
    virtual void log(const std::string& msg) = 0;   // 纯虚函数
};

// 实现1：打印到控制台
class ConsoleLogger : public Logger {
public:
    void log(const std::string& msg) override {
        std::cout << "[Console] " << msg << '\n';
    }
};

// 实现2：假装写到文件
class FileLogger : public Logger {
public:
    explicit FileLogger(const std::string& path) : path_(path) {}
    void log(const std::string& msg) override {
        std::cout << "[File: " << path_ << "] " << msg << '\n';
    }
private:
    std::string path_;
};

// 🏭 工厂函数：根据类型决定创建哪个 Logger
std::unique_ptr<Logger> make_logger(const std::string& type) {
    if (type == "console")
        return std::make_unique<ConsoleLogger>();
    if (type == "file")
        return std::make_unique<FileLogger>("app.log");
    return nullptr;          // 未知类型 → 空指针
}

int main() {
    auto console = make_logger("console");
    if (console) console->log("hello from console");

    auto file = make_logger("file");
    if (file) file->log("hello from file");

    auto unknown = make_logger("email");   // 不存在
    if (unknown)
        unknown->log("never printed");
    else
        std::cout << "(unknown type: 没有这个 logger)\n";

    return 0;
}