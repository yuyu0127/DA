#include <iostream>

void insertion_sort(int a[], int count) {
    for (int j = 1; j < count; j++) {
        int key = a[j];
        int i = j - 1;
        while (i >= 0 && a[i] > key) {
            a[i+1] = a[i];
            i--;
        }
        a[i+1] = key;
    }
}

void display_array(int a[], int count) {
    for (int i = 0; i < count; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
    int count;
    std::cout << "整数列の個数 : ";
    std::cin >> count;
    int array[count];
    std::cout << "整数列を空白区切りで入力 : ";
    for (int i = 0; i < count; i++) {
        std::cin >> array[i];
    }

    display_array(array, count);
    insertion_sort(array, count);
    display_array(array, count);
    return 0;
}
