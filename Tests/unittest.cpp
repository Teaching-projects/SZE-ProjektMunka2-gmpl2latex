#include <gtest/gtest.h>

#include "grammar.tab.h"
#include "Variable.hpp"
#include "Constraint.hpp"
#include "Objective.hpp"


TEST(Multest, resAsExpected){

    EXPECT_EQ(0, 0);

};

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
