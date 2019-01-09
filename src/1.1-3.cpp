#include <iostream>
#include <cmath>

int gcd(int a, int b) {
    int min, max;
    if (a > b) {
        min = b;
        max = a;
    } else {
        min = a;
        max = b;
    }
    if (min > 0) {
        return gcd(min, max % min);
    } else {
        return max;
    }
}

int main() {
    int a, b;
    std::cout << "最大公約数を求める2つの正の整数(空白区切り) : ";
    std::cin >> a >> b;
    if (a <= 0 || b <= 0) {
        std::cout << "2つの正の整数を入力してください" << std::endl;
        return -1;
    }
    std::cout << "GCD(" << a << ", " << b << ") = " << gcd(a, b) << std::endl;

    return 0;
}
