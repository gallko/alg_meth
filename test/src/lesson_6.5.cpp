#include <gtest/gtest.h>
#include <algorithm>
#include <functional>
#include "sequences.h"
#include "../../src/utils.h"
#include "../../src/lesson_6.5.h"


class TestQuickSort: public ::testing::Test
{
public:
    static std::vector<std::vector<int>> increasing;
    static std::vector<std::vector<int>> decreasing;
    static void SetUpTestSuite() {
        for(auto &line: increasing) {
            std::sort(line.begin(), line.end(), std::less<int>());
        }
        for(auto &line: decreasing) {
            std::sort(line.begin(), line.end(), std::greater<int>());
        }
    }
};
std::vector<std::vector<int>> TestQuickSort::increasing = sequences::sequence;
std::vector<std::vector<int>> TestQuickSort::decreasing = sequences::sequence;
TEST_F(TestQuickSort, increasing) {
    for(size_t i = 0; i < increasing.size(); ++i) {
        auto tmp(sequences::sequence[i]);
        lesson_6_5::qsort(tmp.begin(), tmp.end(), [](int op, int el){
            if (op == el) return 0;
            if (el > op) return 1;
            return -1;
        });
        EXPECT_EQ(tmp, increasing[i]);
    }
}
TEST_F(TestQuickSort, decreasing) {
    for(size_t i = 0; i < decreasing.size(); ++i) {
        auto tmp(sequences::sequence[i]);
        lesson_6_5::qsort(tmp.begin(), tmp.end(), [](int op, int el){
            if (op == el) return 0;
            if (el > op) return -1;
            return 1;
        });
        EXPECT_EQ(tmp, decreasing[i]);
    }
}

class TestFull: public ::testing::Test {
private:
    std::streambuf *cin_buf;
    std::streambuf *cout_buf;
protected:
    void SetUp() override {
        cin_buf = std::cin.rdbuf();
        cout_buf = std::cout.rdbuf();
    }
    void TearDown() override {
        std::cout.clear();
        std::cin.clear();
        std::cin.rdbuf(cin_buf);
        std::cout.rdbuf(cout_buf);
    }
};

TEST_F(TestFull, test1) {
    std::istringstream iss{"2 3 0 5 7 10 1 6 11"};
    std::cin.rdbuf(iss.rdbuf());

    std::stringstream result_ss;
    std::cout.rdbuf(result_ss.rdbuf());

    lesson_6_5::main_1();

    EXPECT_TRUE(std::cin.eof());
    EXPECT_FALSE(std::cin.fail());
    EXPECT_FALSE(std::cout.fail());
    EXPECT_EQ(result_ss.str(), "1 0 0 ");
}

TEST_F(TestFull, test2) {
    std::istringstream iss{"6 6 0 3 1 3 2 3 3 4 3 5 3 6 1 2 3 4 5 6"};
    std::cin.rdbuf(iss.rdbuf());
    std::stringstream result_ss{};
    std::cout.rdbuf(result_ss.rdbuf());

    lesson_6_5::main_1();

    EXPECT_TRUE(std::cin.eof());
    EXPECT_FALSE(std::cin.fail());
    EXPECT_FALSE(std::cout.fail());
    EXPECT_EQ(result_ss.str(), "2 3 6 3 2 1 ");
}

TEST_F(TestFull, test3) {
    std::istringstream iss{"10 5 \n"
                           "-2 3\n"
                           "0 3\n"
                           "-1 0\n"
                           "-1 3\n"
                           "0 1\n"
                           "-2 -1\n"
                           "1 3\n"
                           "2 3\n"
                           "1 2\n"
                           "2 3\n"
                           "-3 -1 0 2 3"};
    std::cin.rdbuf(iss.rdbuf());
    std::stringstream result_ss{};
    std::cout.rdbuf(result_ss.rdbuf());

    lesson_6_5::main_1();

    EXPECT_TRUE(std::cin.eof());
    EXPECT_FALSE(std::cin.fail());
    EXPECT_FALSE(std::cout.fail());
    EXPECT_EQ(result_ss.str(), "0 4 5 7 6 ");
}
