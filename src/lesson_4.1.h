#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

namespace lesson_4_1 {
    struct Item final {
        int weight;
        int value;
    };

    using Segment = std::pair<int, int>;

    std::vector <int> get_covering_set(std::vector<Segment> segments) {
        std::vector<int> result;

        std::sort(begin(segments), end(segments), 
            [](const Segment &it1, const Segment &it2) {
                return it1.second < it2.second;
            });
        
        for (const auto &s : segments) {
            if (result.empty() || result.back() < s.first || result.back() > s.second) 
                result.push_back(s.second);
        }

        return result;
    }

    double get_max_knapsack_value(int capacity, std::vector<Item> items) {
        double value = 0.0;

        std::sort(begin(items), end(items), 
            [](const Item &s1, const Item &s2) {
                return static_cast<double>(s1.value) / s1.weight > static_cast<double>(s2.value) / s2.weight;
        });

        // take items while there is empty space in knapsack
        for (auto &item: items) {
            if (capacity > item.weight) {
                // can take full item and continue
                capacity -= item.weight;
                value += item.value;
            } else {
                value += item.value * (static_cast <double>(capacity) / item.weight);
                break;
            }
        }

        return value;
    }


    int main_1(void) {
        int segments_count;
        std::cin >> segments_count;
        std::vector <Segment> segments(segments_count);
        for (auto &s:segments) {
            std::cin >> s.first >> s.second;
        }

        auto points = get_covering_set(std::move(segments));
        std::cout << points.size() << std::endl;
        for (auto point:points) {
            std::cout << point << " ";
        }
        std::cout << std::endl;
        return 0;
    }

    int main_2(void) {
        int number_of_items;
        int knapsack_capacity;
        std::cin >> number_of_items >> knapsack_capacity;
        std::vector <Item> items(number_of_items);
        for (int i = 0; i < number_of_items; i++) {
            std::cin >> items[i].value >> items[i].weight;
        }

        double max_knapsack_value = get_max_knapsack_value(knapsack_capacity, std::move(items));

        std::cout.precision(3);
        std::cout << std::fixed << max_knapsack_value << std::endl;
        return 0;
    }

    int main_3(void)  {
        int k, i = 0, sum = 0;
        std::vector<int> result;
        std::cin >> k;

        while (sum < k)
        {
            sum += ++i;
            result.push_back(i);
        }
        if (sum > k) {
            sum -= result.back(); result.pop_back();
            sum -= result.back(); result.pop_back();
            result.push_back(k - sum);
        }

        std::cout << result.size() << std::endl;
        for (auto i: result) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
        return 0;
    }
}