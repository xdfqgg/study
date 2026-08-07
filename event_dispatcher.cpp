#include <functional>
#include <iostream>
#include <map>

class Event {
public:
    using Handler = std::function<void(int)>;

    int subscribe(Handler h) {
        int id = ++last_id_;          // 发一个递增的"粉丝号"
        handlers_[id] = std::move(h); // 存进通讯录
        return id;                    // 把 id 还给订阅者（以后用它取关）
    }
    void unsubscribe(int id) {
        handlers_.erase(id);          // 从通讯录删掉这个 id
    }
    void notify(int v) {
        for (auto& kv : handlers_) {  // 遍历通讯录
            if (kv.second) kv.second(v);   // 逐个调用还订阅着的回调
        }
    }

private:
    std::map<int, Handler> handlers_;   // id → 回调
    int last_id_ = 0;                   // 发号器
};

int main() {
    Event ev;
    int external = 100;

    int id1 = ev.subscribe([&external](int x) {
        std::cout << "h1: " << x + external << '\n';   // 捕获 external
    });
    int id2 = ev.subscribe([](int x) {
        std::cout << "h2: " << x * 2 << '\n';
    });

    ev.notify(5);        // 两个都收到 → h1:105  h2:10
    ev.unsubscribe(id1); // h1 取关
    ev.notify(7);        // 只剩 h2 → h2:14
    return 0;
}