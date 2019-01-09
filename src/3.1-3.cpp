#include <iostream>
#include <random>

std::random_device rnd;

void display_array(int const a[], int const count)
{
    for (int i = 0; i < count; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

int quicksort(int a[], int first, int last)
{
    if (first == last) {
        return 1;
    }

    int p1, p2, p3, pivot;
    p1 = a[rnd() % (last - first) + first];
    p2 = a[rnd() % (last - first) + first];
    p3 = a[rnd() % (last - first) + first];

    if ((p2 <= p1 && p1 <= p3) || (p3 <= p1 && p1 <= p2))
        pivot = p1;
    if ((p3 <= p2 && p2 <= p1) || (p1 <= p2 && p2 <= p3))
        pivot = p2;
    if ((p1 <= p3 && p3 <= p2) || (p2 <= p3 && p3 <= p1))
        pivot = p3;

    int q;
    while (1) {
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

    return 0;
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