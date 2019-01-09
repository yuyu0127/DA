#include <iostream>
#include <cmath>

bool is_prime(int n)
{
    if (n == 1)
    {
        return false;
    }
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int num;
    std::cout << "判定する正の整数 : ";
    std::cin >> num;
    if (num <= 0)
    {
        std::cout << "正の整数を入力してください" << std::endl;
        return -1;
    }
    std::cout << num << (is_prime(num) ? "は素数です" : "は素数ではありません") << std::endl;
    return 0;
}