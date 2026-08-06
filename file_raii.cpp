#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

class FileRAII {
    public:
    explicit FileRAII(const char* path, const char* mode){
        fp_ = std::fopen(path, mode);
        if(!fp_){
            throw std::runtime_error("Failed to open file");
        }
    }

    FileRAII(const FileRAII&) = delete; // 禁止拷贝构造
    FileRAII& operator=(const FileRAII&) = delete; // 禁止拷贝赋值

    FileRAII(FileRAII&& other) noexcept :fp_(other.fp_){
        other.fp_ = nullptr; // 转移所有权
    }
    FileRAII& operator=(FileRAII&& other) noexcept {
        if(this != &other){
            close();
            fp_ = other.fp_;
            other.fp_ = nullptr; // 转移所有权
        }
        return *this;
    }
    ~FileRAII(){close();}

    std::string readLine() {
        if (!fp_) return{};
        char buf[512];
        if(!std::fgets(buf, sizeof(buf), fp_))return{};
        return std::string(buf);
    }
    private:
    void close(){
        if(fp_){
            std::fclose(fp_);
            fp_ = nullptr;
        }
        
    }
    std::FILE* fp_{nullptr};
};



int main() {
    try {
        FileRAII f1("sample.txt", "r");
        auto line = f1.readLine();
        std::cout << line;
        FileRAII f2 = std::move(f1);   // 移动：资源从 f1 转到 f2
        // f1 现在是空的，f2 持有文件
    } catch (const std::exception& e) {
        std::cerr << "err: " << e.what() << "\n";
    }
    return 0;
}