#include <vector>
#include <iostream>
#include <functional>

namespace lesson_4_3 {

template<typename T, typename compare_t = std::greater<T>, int d = 2>
class heap {
public:
    void reserve(int n) {
        data.reserve(n);
    }

    void insert(T elem) {
        data.push_back(elem);
        shiftUp();
    };

    T extract() {
        std::swap(*data.begin(), *(data.end() - 1));
        auto r = std::move(data.back());
        data.pop_back();
        siftDown();
        return r;
    };

private:
    std::vector<T> data;
    compare_t comparator;

    size_t parent(size_t i) const noexcept {
        return i ? (i - 1) / d : i;
    }

    size_t child_for_swap (size_t h) {
        size_t child = h * d + 1;
        if (child >= data.size()) return h;
        for(auto it = child; it - child < d && it < data.size(); ++it) {
            if (comparator(data[it], data[h]))
                h = it;
        }
        return h;
    }

    void shiftUp() {
        auto i = data.size() - 1;
        auto p = parent(i);
        while (i != p && comparator(data[i], data[p])) {
            std::swap(data[i], data[p]);
            i = p;
            p = parent(i);
        }
    };

    void siftDown() {
        auto i = 0;
        auto child_i = child_for_swap(i);
        while (i != child_i) {
            std::swap(data[i], data[child_i]);
            i = child_i;
            child_i = child_for_swap(i);
        }
    };
};

int main_1() {
    heap<int> h;
    int count = 0;
    std::cin >> count;
    h.reserve(count);
    for (auto i = 0; i < count; ++i) {
        std::string cmd;
        std::cin >> cmd;
        if (cmd == "Insert") {
            int x;
            std::cin >> x;
            h.insert(x);
        } else if (cmd == "ExtractMax") {
            std::cout << h.extract() << std::endl;
        }
    }
}
}