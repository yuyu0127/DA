#include <iostream>


void merge_sort(int a[], int left, int right) {
    int mid, i, j, k;
    int tmp[right];
    if (left >= right) {
        return;
    }

    mid = (left + right) / 2;
    merge_sort(a, left, mid);
    merge_sort(a, mid+1, right);

    for (i = left; i <= mid; i++) {
        tmp[i] = a[i];
    }
    for (i = mid+1, j = right; i <= right; i++, j--) {
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
    merge_sort(array, 0, count-1);
    display_array(array, count);
    return 0;
}
