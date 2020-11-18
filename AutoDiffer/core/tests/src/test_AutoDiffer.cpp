/* system header files */
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <utility>
#include <vector>
#include <math.h>

/* googletest header files */
#include "gtest/gtest.h"

/* header files */
#include "ADValue.hpp"
#include "ADNode.hpp"
#include "Parser.hpp"
#include "AutoDiffer.hpp"
#include "test_vars.h"

void AutoDiffer_testcheck(){
    printf("Starting AutoDiffer tests...\n");
}

TEST(autodiffer_test, int){
    AutoDiffer<int> ad;
    ad.SetSeed("x", /*value=*/7, /*dval=*/1);

    std::pair<Status, int> res = ad.Derive("((x+5)^3)");
    ASSERT_EQ(res.first.code, ReturnCode::success);
    EXPECT_EQ(res.second, 432);
}

TEST(autodiffer_test, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/7, /*dval=*/1);

    std::pair<Status, double> res = ad.Derive("(x/3)");
    ASSERT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second, 0.3333, 0.001);
}

TEST(autodiffer_test2, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/1., /*dval=*/1.);

    std::pair<Status, double> res = ad.Derive("(tan((x/3)))");
    ASSERT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second, 1.5, 0.001);
}
