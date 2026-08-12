// 头文件保护：防止一个文件被 include 两次导致重复定义
#ifndef DEMO_UTILS_H
#define DEMO_UTILS_H

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>

// 给 std::filesystem 起个短别名，少打字
namespace fs = std::filesystem;

// ① 自定义异常：继承 std::runtime_error（标准做法）
struct MyError : std::runtime_error
{
    MyError(const std::string &s) : std::runtime_error(s) {}
};

// ② 除法：b == 0 时抛异常
inline int divide(int a, int b)
{
    if (b == 0)
        throw MyError("division by zero");
    return a / b;
}

// ③ 稳健保存：先写临时文件，再原子替换
inline bool safer_save(const fs::path &path, const std::string &data)
{
    fs::path tmp = path; // 临时文件路径 = 原路径 + ".tmp"
    tmp += ".tmp";
    {
        std::ofstream out(tmp, std::ios::binary); // 打开临时文件
        if (!out)
            return false; // 打开失败 → 直接失败
        out << data;      // 写数据
        if (!out)
            return false; // 写完检查状态
    } // ← 离开这个块，out 自动关闭（RAII）

    std::error_code ec;        // 用 error_code 接收错误（不抛异常版本）
    fs::rename(tmp, path, ec); // 把临时文件"改名"成正式文件
    if (ec)
    {                    // 改名失败
        fs::remove(tmp); // 清理临时文件
        return false;
    }
    return true;
}

#endif