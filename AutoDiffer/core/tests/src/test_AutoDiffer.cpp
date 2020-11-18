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
