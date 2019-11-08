#include <limits>
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>

namespace lesson_4_2 {

template<typename type_letter>
class Node final {
public:
    using foreach_func = std::function<void(const type_letter& ch, const std::string& code)>;
    static const type_letter EMPTY_LETTER = std::numeric_limits<type_letter>::max();

    static std::unique_ptr<Node> make_dict_from_text(const std::string& str) {
        std::vector<Node*> queue;

        if (str.empty()) return nullptr;

        for(auto ch: str) {
            auto it = std::find_if(queue.begin(), queue.end(),
                [&ch](Node* it) { return it->pLetter == ch; });
            if (it != queue.end())
                ++(*it)->pFreq;
            else
                queue.push_back(new Node(ch, 1));
        }

        std::sort(queue.begin(), queue.end(), [](const Node* i1, const Node* i2) {
            return i1->pFreq > i2->pFreq;
        });

        while (queue.size() > 1) {
            auto left = queue.back(); queue.pop_back();
            auto right = queue.back(); queue.pop_back();
            auto new_node = new Node(std::unique_ptr<Node>(left), std::unique_ptr<Node>(right));
            auto it = std::lower_bound(queue.begin(), queue.end(), new_node, [](const Node* it1, const Node* it2) {
                return it1->pFreq >= it2->pFreq;
            });
            queue.insert(it, new_node);
        }
        Node* top = queue.back(); queue.pop_back();
        if (!top->pLeft && !top->pRight) {
            top = new Node(std::unique_ptr<Node>(top), nullptr);
        }
        return std::unique_ptr<Node>(top);
    };

    size_t getCountLetter() const {
        return countLetter(this);
    }

    size_t getLengthBinary() const {
        return lengthBinary(this);
    }

    void foreach_letter(foreach_func func) const {
        return foreach(func, this, std::string());
    }

    std::string codingLetter(const type_letter &letter) {
        return coding(this, letter, std::string());
    }

private:
    Node(type_letter ch, size_t freq)
        : pLeft(nullptr), pFreq(freq), pRight(nullptr), pLetter(std::move(ch)) 
    {/* empty */};

    Node(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
        : pLeft(std::move(left)), pRight(std::move(right)), pFreq(0), pLetter(EMPTY_LETTER)
    {
        pFreq += pLeft ? pLeft->pFreq : 0;
        pFreq += pRight ? pRight->pFreq : 0;
    };

    static size_t countLetter(const Node * const n) {
        // recursive method
        if (!n) return 0;
        if (n->pLetter != Node::EMPTY_LETTER) return 1;
        return countLetter(n->pLeft.get()) + countLetter(n->pRight.get());
    };

    static size_t lengthBinary(const Node * const n) {
        // recursive method
        if (!n || n->pLetter != Node::EMPTY_LETTER) return 0;
        return n->pFreq + lengthBinary(n->pLeft.get()) + lengthBinary(n->pRight.get());
    };

    static void foreach(foreach_func func, const Node * const n, std::string prefix) {
        if (!n) return;
        if (n->pLetter != Node::EMPTY_LETTER) {
            func(n->pLetter, prefix);
            return;
        }
        foreach(func, n->pLeft.get(), prefix + std::string("0"));
        foreach(func, n->pRight.get(), prefix + std::string("1"));
    };

    static std::string coding(const Node * const n, const type_letter &letter, std::string code) {
        if (!n) return std::string();
        if (n->pLetter == letter) return code;

        auto s_left = coding(n->pLeft.get(), letter, code + std::string("0"));
        if (!s_left.empty()) return s_left;

        auto s_right = coding(n->pRight.get(), letter, code + std::string("1"));
        if (!s_right.empty()) return s_right;

        return std::string();
    }

    std::unique_ptr<Node> pLeft, pRight;
    type_letter pLetter;
    size_t pFreq;
};

int main_1() {
    std::string str;
    std::cin >> str;

    auto dict = Node<char>::make_dict_from_text(str);
    std::cout << dict->getCountLetter() << " " << dict->getLengthBinary() << std::endl;
    dict->foreach_letter([](const char &ch, const std::string& code) {
        std::cout << ch << ": " << code << std::endl;
    });
    for(auto &ch: str)
        std::cout << dict->codingLetter(ch);
    std::cout << std::endl;

    return 0;
}
}