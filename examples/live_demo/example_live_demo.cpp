/**
 * @file    example_live_demo.cpp
 * @brief   Demonstrates the used of the
 *          templated AutoDiffer class.
 *
 *    
 * To run this example run `make` in this directory, followed by 
 * `./example_live_demo`
 *
 */

#include <bits/stdc++.h>
#include <chrono>
#include <iostream>
#include <vector>

#include "../../AutoDiffer/include/AutoDiffer.hpp"

int main() {
    /* f(x) = x^2 + 5 at x = -1
     * 
     * f(-1) = 6
     * f'(-1) = -2
     * 
     */
    
    AutoDiffer<double> ad;

    ad.SetSeed("x", -1, 1);

    std::pair<Status, ADValue<double>> res = ad.Derive("((x^2)+5)");

    assert(res.first.code == ReturnCode::success);

    std::cout << res.second.val() << ' ' << res.second.dval(0) << std::endl;



    return 0;
}
