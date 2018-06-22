//
// Created by garrett on 6/19/18.
//

#include "gtest/gtest.h"

TEST(basic_check, test_eq) {
    EXPECT_EQ(0,0);
    EXPECT_EQ(1,1);
    EXPECT_EQ(5,5);
}

//int main(int argc, char **argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
//}