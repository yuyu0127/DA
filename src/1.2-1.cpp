#include <iostream>
#include <cmath>
#include <iomanip>

typedef long double d_type;

/* 再帰(定義どおり) */
d_type fib_rec(int n) {
    if (n <= 1) {
        return n;
    }
    return fib_rec(n-2) + fib_rec(n-1);
}

/* 反復 */
d_type fib_ite(int n) {
    if (n==0) return 0;
    d_type a = 0;
    d_type b = 1;
    while(n > 1) {
        d_type temp = a;
        a = b;
        b += temp;
        n--;
    }
    return b;
}

/* 末尾再帰 */
d_type fib_trec(int n, d_type a, d_type b) {
    if (n == 0) {
        return 0;
    }
    if (n > 1) {
        return fib_trec(n-1, b, a+b);
    } else {
        return b;
    }
}

int main()
{
    int n;
    std::cout << "n番目のフィボナッチ数列を表示します : ";
    std::cin >> n;
    if (n <= -1) {
        std::cout << "0以上の整数を入力してください" << std::endl;
        return -1;
    }
    std::cout << std::setprecision(16);
    std::cout << "F(" << n << ") = " << fib_ite(n) << std::endl;

    return 0;
}
