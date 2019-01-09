#include <iostream>

void display_array(int const a[], int const count)
{
    for (int i = 0; i < count; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

void quicksort(int a[], int first, int last)
{
    if (first == last) {
        return;
    }

    int pivot = a[first];
    int q;

    while (true) {
        int i = first;
        int j = last;
        while (i < last && a[i] < pivot) {
            i++;
        }
        while (j > first && a[j] >= pivot) {
            j--;
        }
        if (i >= j) {
            q = j;
            break;
        }

        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }

    quicksort(a, first, q);
    quicksort(a, q + 1, last);

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
    quicksort(array, 0, count - 1);
    std::cout << "[sorted array]" << std::endl;
    display_array(array, count);

    return 0;
}