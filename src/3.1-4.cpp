#include <cmath>
#include <iostream>

using namespace std;

void display_array(int const a[], int const count)
{
    for (int i = 0; i < count; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

void radix_sort(int a[], int const count)
{
    /* 最大桁数を計算 */
    int max_digit = 0;
    for (int i = 0; i < count; i++) {
        int digit = log10(a[i]) + 1;
        max_digit = (max_digit < digit) ? digit : max_digit;
    }

    int r = 1; /* d桁目の値を求めるためのやつ */
    for (int d = 0; d < max_digit; d++) {
        /* 10*count の2次元配列を用意 */
        int bucket[10][count];
        /* bucketのどこまでが埋まっているか */
        int bucket_count[10];

        /* 配列を0で初期化 */
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < count; j++) {
                bucket[i][j] = 0;
            }
            bucket_count[i] = 0;
        }

        for (int i = 0; i < count; i++) {
            int key = (a[i] / r) % 10; /* a[i]のd桁目 */
            bucket[key][bucket_count[key]++] = a[i];
        }

        /* もとの配列に代入 */
        int k = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < bucket_count[i]; j++) {
                a[k] = bucket[i][j];
                k++;
            }
        }

        r *= 10;
    }
}

int main()
{
    int count;
    cout << "Enter the number of array : ";
    cin >> count;
    if (count <= 0) {
        cout << "Enter the positive integer!" << endl;
        return -1;
    }

    int array[count];
    cout << "Enter the values of array : ";
    for (int i = 0; i < count; i++) {
        cin >> array[i];
    }

    cout << "[source array]" << endl;
    display_array(array, count);
    radix_sort(array, count);
    cout << "[sorted array]" << endl;
    display_array(array, count);

    return 0;
}