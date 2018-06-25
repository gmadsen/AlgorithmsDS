//
// Created by garrett on 6/21/18.
//
#include "gtest/gtest.h"
#include "algorithmsDS.h"
#include <mult_algorithm.h>
#include "algorithmsDS.h"


using namespace std;
using namespace AlgorithmDS;

// test addition basic
TEST(test_find_sum, small) {
        string num1 = "1";
        string num2 = "2";
        string ans = find_sum(num1, num2);
        ASSERT_EQ(ans, "3");
}

// test addition long
TEST(test_find_sum, large) {
        string num1 =
        "111111111111111111111111111111111111111111111111111111111111111111111111"
        "1111111111111111111111111111111111111111";
        string num2 =
        "999999999999999999999999999999999999999999999999999999999999999999999999"
        "9999999999999999999999999999999999999999";
        string ans = find_sum(num1, num2);
        ASSERT_EQ(ans,
        "111111111111111111111111111111111111111111111111111111111111111"
        "11111111111111111111111111111111111111111111111110");
}

TEST(test_find_diff, smallpos) {
        string num1 = "87";
        ASSERT_EQ(find_diff(num1, "7"), "80");
        ASSERT_EQ(find_diff(num1, "80"), "7");
        ASSERT_EQ(find_diff(num1, "6"), "81");
}

TEST(test_find_diff, large) {
        string num1 =
        "100000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000";
        string num2 =
        "999999999999999999999999999999999999999999999999999999999999999999999999"
        "999999999999999999999999999991";
        ASSERT_EQ(find_diff(num1, num2), "9");
}

TEST(test_karatsuba, small) {
    ASSERT_EQ(karatsuba("12", "13"), "156");
    ASSERT_EQ(karatsuba("123", "123"), "15129");
}

TEST(test_merge, small) {
        vector<int> left{1, 5, 7, 8, 9};
        vector<int> right{2, 3, 4, 11, 40};
        vector<int> expected{1, 2, 3, 4, 5, 7, 8, 9, 11, 40};
        ASSERT_EQ(expected, merge(left, right));
}

TEST(test_merge_sort, small) {
        vector<int> input{1, 3, 2, 5, 7, 4, 6, 8, 9};
        vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
        ASSERT_EQ(expected, merge_sort(input));
}

TEST(test_inversion_count, small) {
        vector<int> unsorted{1, 2, 3, 5, 6, 7, 4, 8, 9};
        int expected = 3;
        long long int actual = 0;
        inversion_count(unsorted, actual);
        ASSERT_EQ(expected, actual);
}

TEST(test_vector_partition, small) {
        vector<int> unsorted{9, 8, 7, 6, 5, 4, 3, 2, 1};
        vector<int> expected{1, 5, 4, 3, 2, 6, 9, 8, 7};
        vector_partition(unsorted.begin(), unsorted.end(), unsorted.begin() + 3);
        ASSERT_EQ(unsorted, expected);
}

TEST(test_vector_quicksort, small) {
        vector<int> unsorted{4, 3, 2, 1};
        vector<int> expected{1, 2, 3, 4};
        long long int count = 0;
        quicksort(unsorted.begin(), unsorted.end(), count);
        ASSERT_EQ(unsorted, expected);
}

TEST(test_quicksort, mid) {
        vector<int> unsorted{20, 12, 13, 11, 14, 18, 19, 17, 16, 15};
        vector<int> expected{11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
        long long count = 0;
        quicksort(unsorted.begin(), unsorted.end(), count);
        ASSERT_EQ(unsorted, expected);
}

TEST(test_min_cut_contraction, small) {
        list<pair<int, list<int>>> graph;
        graph.emplace_back(1, list<int>{2, 3});
        graph.emplace_back(2, list<int>{1, 3});
        graph.emplace_back(3, list<int>{1, 2});
        int value = min_cut_contraction(graph);
        cout << "value is : " << value << endl;
}
TEST(test_min_cut_contraction, diamond) {
        list<pair<int, list<int>>> graph;
        graph.emplace_back(1, list<int>{2, 3, 4});
        graph.emplace_back(2, list<int>{1, 4});
        graph.emplace_back(3, list<int>{1, 4});
        graph.emplace_back(4, list<int>{1, 2, 3});
        unsigned long n = graph.size();
        unsigned long iterations = n * n * ceil(log(n));
        int value = iterations;
        for (int i = 0; i < iterations; ++i) {
            int single_value = min_cut_contraction(graph);
            if (single_value < value) value = single_value;
        }
}

