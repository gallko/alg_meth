#include <limits>
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>
#include <sstream>

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

    static std::unique_ptr<Node> make_head() {
        return std::unique_ptr<Node>(new Node());
    }

    size_t get_count_letter() const {
        return count_letter(this);
    }

    size_t get_length_binary() const {
        return length_binary(this);
    }

    void foreach_letter(foreach_func func) const {
        return foreach(func, this, std::string());
    }

    std::string coding_letter(const type_letter &letter) const {
        return coding(this, letter, std::string());
    }

    std::string decoding_letter(const std::string& code) const {
        auto it_code = code.cbegin();
        std::stringstream ss;
        while (it_code != code.cend()) {
            Node const* it = this;
            while (it->pLetter == EMPTY_LETTER) {
                if (*it_code == '0') it = it->pLeft.get();
                else if (*it_code == '1') it = it->pRight.get();
                else throw std::logic_error(
                            std::string("Illegal symbol in the code: '")
                            + std::string(1, *it_code) + std::string("'"));
                ++it_code;
            }
            ss << it->pLetter;
        }
        return ss.str();
    }

    int add_leaf(const type_letter& ch, const std::string& code) {
        auto it = this;
        for(const auto& b: code) {
            it = create_or_get_node(it, b);
            if (!it || it->pLetter != EMPTY_LETTER) return -1;
        }
        it->pLetter = ch;
        return 0;
    }

private:
    Node() : pLeft(nullptr), pRight(nullptr),  pFreq(0), pLetter(EMPTY_LETTER)
    {/* empty */}

    Node(type_letter ch, size_t freq)
        : pLeft(nullptr), pFreq(freq), pRight(nullptr), pLetter(std::move(ch)) 
    {/* empty */};

    Node(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
        : pLeft(std::move(left)), pRight(std::move(right)), pFreq(0), pLetter(EMPTY_LETTER)
    {
        pFreq += pLeft ? pLeft->pFreq : 0;
        pFreq += pRight ? pRight->pFreq : 0;
    };

    static size_t count_letter(const Node * const n) {
        // recursive method
        if (!n) return 0;
        if (n->pLetter != Node::EMPTY_LETTER) return 1;
        return count_letter(n->pLeft.get()) + count_letter(n->pRight.get());
    };

    static size_t length_binary(const Node * const n) {
        // recursive method
        if (!n || n->pLetter != Node::EMPTY_LETTER) return 0;
        return n->pFreq + length_binary(n->pLeft.get()) + length_binary(n->pRight.get());
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

    static Node* create_or_get_node(Node* node, const char &bit) {
        Node* it = nullptr;
        if (bit == '0')
            it = node->pLeft ? node->pLeft.get() : (node->pLeft = std::unique_ptr<Node>(new Node())).get();
        else if (bit == '1')
            it = node->pRight ? node->pRight.get() : (node->pRight = std::unique_ptr<Node>(new Node())).get();
        return it;
    }

    std::unique_ptr<Node> pLeft, pRight;
    type_letter pLetter;
    size_t pFreq;
};

int main_1() {
    std::string str;
    std::cin >> str;

    auto dict = Node<char>::make_dict_from_text(str);
    std::cout << dict->get_count_letter() << " " << dict->get_length_binary() << std::endl;
    dict->foreach_letter([](const char &ch, const std::string& code) {
        std::cout << ch << ": " << code << std::endl;
    });
    for(auto &ch: str)
        std::cout << dict->coding_letter(ch);
    std::cout << std::endl;

    return 0;
}

int main_2() {
    int k, l;
    char ch;
    std::string str;
    std::cin >> k >> l;
    auto dict = Node<char>::make_head();
    for(auto i = 0; i < k; ++i) {
        std::cin >> ch >> str >> str;
        dict->add_leaf(ch, str);
    }
    std::cin >> str;
    str.resize(l);
    auto s = dict->decoding_letter(str);
    std::cout << s << std::endl;
    return 0;
}

}