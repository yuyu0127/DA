#include <iostream>

void display_array(int const a[], int const count)
{
    for (int i = 0; i < count; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

void merge_sort(int a[], int left, int right)
{
    int mid, i, j, k;
    int tmp[right];
    if (left >= right) {
        return;
    }

    mid = (left + right) / 2;
    merge_sort(a, left, mid);
    merge_sort(a, mid + 1, right);

    for (i = left; i <= mid; i++) {
        tmp[i] = a[i];
    }
    for (i = mid + 1, j = right; i <= right; i++, j--) {
        tmp[i] = a[j];
    }

    i = left;
    j = right;

    for (k = left; k <= right; k++) {
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
    merge_sort(array, 0, count - 1);
    std::cout << "[n/3]th smallerst value : " << array[count - (count + 2) / 3] << std::endl;

    return 0;
}
