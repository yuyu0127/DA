#include <iostream>

void display_array(int const a[], int const count)
{
    for (int i = 0; i < count; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

void merge_sort(int a[], int first, int last)
{
    if (first >= last) {
        return;
    }

    int mid = (first + last) / 2;
    merge_sort(a, first, mid);
    merge_sort(a, mid + 1, last);

    int tmp[last];

    for (int i = first; i <= mid; i++) {
        tmp[i] = a[i];
    }
    for (int i = mid + 1, j = last; i <= last; i++, j--) {
        tmp[i] = a[j];
    }

    for (int i = first, j = last, k = first; k <= last; k++) {
        if (tmp[i] <= tmp[j]) {
            a[k] = tmp[i];
            i++;
        } else {
            a[k] = tmp[j];
            j--;
        }
    }

    return;
}

int main()
{
    int count;
    std::cout << "Enter the number of array : ";
    std::cin >> count;
    if (count <= 0) {
        std::cout << "Enter the positive integer!" << std::endl;
        return -1;
    }

    int array[count];
    std::cout << "Enter the values of array : ";
    for (int i = 0; i < count; i++) {
        std::cin >> array[i];
    }
    std::cout << "[source array]" << std::endl;
    display_array(array, count);
    merge_sort(array, 0, count - 1);
    std::cout << "[sorted array]" << std::endl;
    display_array(array, count);

    return 0;
}