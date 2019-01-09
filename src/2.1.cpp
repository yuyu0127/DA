#include <iostream>

void display_array(int const a[], int const count)
{
    for (int i = 0; i < count; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

void max_heapify(int a[], int i, int const count)
{
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int largest;

    if (l < count && a[l] > a[i]) {
        largest = l;
    } else {
        largest = i;
    }

    if (r < count && a[r] > a[largest]) {
        largest = r;
    }

    if (largest != i) {
        int temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;
        max_heapify(a, largest, count);
    }
}

void build_max_heap(int a[], int const count)
{
    for (int i = (count - 1) / 2; i >= 0; i--) {
        max_heapify(a, i, count);
    }
}

int heap_extract_max(int a[], int const count)
{
    if (count <= 0) {
        std::cerr << "Heap Error" << std::endl;
        return -1;
    }
    int max = a[0];
    a[0] = a[count - 1];
    max_heapify(a, 0, count - 1);
    return max;
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

    std::cout << "[heapified array]" << std::endl;
    build_max_heap(array, count);
    display_array(array, count);

    return 0;
}
