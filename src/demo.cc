#include <iostream>

int GetLarger(int a, int b) {
    if (a == b || a > b) {
        return a;
    }
    return b;
}

bool IsPositiveOdd(int a) {
    if (a > 0 && a % 2 != 0) {
        return true;
    }
    return false;
} 

int main () {
    std::cout << GetLarger(5, 9) << std::endl;
    std::cout << IsPositiveOdd(5) << std::endl;
}