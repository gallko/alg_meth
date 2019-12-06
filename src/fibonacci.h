#include <cassert>
#include <iostream>
#include <array>
#include <vector>

class Fibonacci final {
public:
    static int get(int n) {
        assert(n >= 0);
        std::array<int, 40> m{0,1};
        for(auto it = m.begin()+2; it < m.end(); ++it)
            *it = *(it-2) + *(it-1);
        return m[n];
    }

    static int get_last_digit(int n) {
        assert(n >= 1);
        int f1 = 0, f2 = 1;
        for(int i = 2; i <= n; ++i) {
            int tmp = (f1 + f2) % 10;
            f1 = f2; f2 = tmp;
        }
        return f2;
    }

    static int get_remainder(int64_t n, int m) {
        assert(n >= 1);
        assert(m >= 2);
        std::vector<int> v{0,1};
        for (auto i = 2LL; i < m*m+1; i++)
        {
            v.push_back((v[i - 2] + v[i - 1]) % m);
            if (*(v.end() - 2) == 0 && *(v.end() - 1) == 1)
                break;

        }        
        return v[n % (v.size() - 2)];
    }
};

template <class Int>
Int gcd(Int a, Int b) {
    assert(a > 0 && b > 0);
    // optimize this function
    do
        if (a < b) std::swap(a, b);
    while( (a %= b) != 0);
    return b;
}

template <class Int>
Int gcd_recursive(Int a, Int b) {
    if (a == 0) return b;
    if (b == 0) return a;
    return (a >= b) ? 
        gcd_recursive(a % b, b) : 
        gcd_recursive(a, b % a);
}

int fibonacci_main() {
    std::cout << gcd(14159572, 63967072) << std::endl;
    std::cout << gcd_recursive(14159572, 63967072) << std::endl;
    return 0;
}
