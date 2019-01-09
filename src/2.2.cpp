#include <iostream>

const int ARRAY_LENGTH = 10000;

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

void heap_insert_max(int a[], int num, int const count)
{
    if (count > ARRAY_LENGTH) {
        std::cout << "Heap overflow!" << std::endl;
        return;
    }

    int i = count - 1;
    while (i > 0 && a[(i - 1) / 2] < num) {
        a[i] = a[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    a[i] = num;
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

    int array[ARRAY_LENGTH];
    std::cout << "Enter the values of array : ";
    for (int i = 0; i < count; i++) {
        std::cin >> array[i];
    }

    std::cout << "[Source array]" << std::endl;
    display_array(array, count);

    std::cout << "[Heapified array]" << std::endl;
    build_max_heap(array, count);
    display_array(array, count);

    int insert_num;
    std::cout << "Enter the number to insert : ";
    std::cin >> insert_num;
    count++;

    heap_insert_max(array, insert_num, count);
    std::cout << "[Inserted array]" << std::endl;
    display_array(array, count);
    return 0;
}
