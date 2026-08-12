// test_examples.cpp —— Catch2 单元测试
// 作用：验证 demo_utils.h 里的 divide 和 safer_save 行为是否正确

#define CATCH_CONFIG_MAIN // ★ 魔法开关：让 Catch2 自动生成 main()（你就不用自己写 main）
#include "catch.hpp"      // 引入 Catch2 测试框架（单头文件版 v2）
#include "demo_utils.h"   // 引入"被测代码"：divide、safer_save

#include <fstream>  // 读文件用
#include <iterator> // istreambuf_iterator 用

// ===== 测试 1：divide 正常情况（值对不对） =====
TEST_CASE("divide normal cases", "[divide]") // 定义一个测试用例：名字 + 标签
{
    // REQUIRE = "这个条件必须成立"，不成立 → 该测试失败
    REQUIRE(divide(10, 2) == 5);  // 10 / 2 应该等于 5
    REQUIRE(divide(10, 5) == 2);  // 10 / 5 应该等于 2
    REQUIRE(divide(-6, 3) == -2); // 负数除法结果也要对
}

// ===== 测试 2：divide 除零时必须抛异常 =====
TEST_CASE("divide throws on zero", "[divide]")
{
    // 断言：调用 divide(10,0) 必须抛出 MyError 类型（没抛/抛别的 → 失败）
    REQUIRE_THROWS_AS(divide(10, 0), MyError);
    // 断言：抛出的错误信息必须正好是 "division by zero"
    REQUIRE_THROWS_WITH(divide(10, 0), "division by zero");
}

// ===== 测试 3：safer_save 写文件 + 校验（流程最完整） =====
TEST_CASE("safer_save writes and verifies", "[fs]")
{
    namespace fs = std::filesystem; // 短别名（头文件里有，这里再写一次也行）

    // ① 准备"临时测试目录"（放在系统临时文件夹里，不污染你的项目目录）
    fs::path dir = fs::temp_directory_path() / "cpp10_test"; // 例如 C:\...\Temp\cpp10_test
    fs::create_directories(dir);                             // 目录不存在就创建它

    fs::path p = dir / "hello.txt"; // 目标文件路径 = 临时目录\hello.txt
    fs::remove(p);                  // ★ Windows 上 rename 不覆盖已存在文件，所以先删旧的

    // ② 调用被测函数：写文件
    REQUIRE(safer_save(p, "hello world\n")); // 应该返回 true（写成功）
    REQUIRE(fs::exists(p));                  // 文件应该确实存在

    // ③ 把文件内容读回来，验证写入是否正确
    std::string content; // 用来存读到的内容
    {
        std::ifstream in(p); // 打开文件流，准备读
        // 用"字符迭代器"把文件所有字符读进 string（istreambuf_iterator = 逐字符读）
        content.assign((std::istreambuf_iterator<char>(in)),
                       std::istreambuf_iterator<char>());
    } // ★ 离开这个块，in 自动关闭（RAII！Windows 上文件没关闭就不能删）

    REQUIRE(content == "hello world\n");       // 读回来的内容应该一字不差
    REQUIRE(!fs::exists(p.string() + ".tmp")); // 临时文件 .tmp 应该已被清理

    // ④ 清理：删掉整个测试目录（测试不留垃圾）
    fs::remove_all(dir);
}
