#define __USE_MINGW_ANSI_STDIO 0

#include <chrono>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

using namespace std;
using namespace chrono;

int tmp[1000000];
int calc_count;
random_device seed_gen;
mt19937 mt;

void display_array(int a[], int count)
{
    for (int i = 0; i < count; i++) {
        // cout << a[i] << " ";
    }
    // cout << endl;
}

/* 挿入ソート */
void insertion_sort(int a[], int count)
{
    for (int j = 1; j < count; j++) {
        int key = a[j];
        int i = j - 1;
        while (i >= 0 && a[i] > key) {
            a[i + 1] = a[i];
            i--;
        }
        a[i + 1] = key;
    }
}

/* ヒープソート */
void min_heapify(int a[], int i, int const count)
{

    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int smallest;

    if (l < count && a[l] < a[i]) {
        smallest = l;
    } else {
        smallest = i;
    }

    if (r < count && a[r] < a[smallest]) {
        smallest = r;
    }

    if (smallest != i) {
        int temp = a[i];
        a[i] = a[smallest];
        a[smallest] = temp;
        min_heapify(a, smallest, count);
    }
}

void build_min_heap(int a[], int const count)
{
    for (int i = (count - 1) / 2; i >= 0; i--) {
        min_heapify(a, i, count);
    }
}

int heap_extract_min(int a[], int const count)
{
    if (count <= 0) {
        return -1;
    }
    int max = a[0];
    a[0] = a[count - 1];
    min_heapify(a, 0, count - 1);
    return max;
}

void heap_sort(int a[], int const count)
{
    build_min_heap(a, count);
    int b[count];
    memcpy(b, a, sizeof(b));
    for (int i = 0; i < count; i++) {
        a[i] = heap_extract_min(b, count - i);
    }
}

/* マージソート */
void merge_sort(int a[], int first, int last)
{
    int mid, i, j, k;
    if (first >= last) {
        return;
    }

    mid = (first + last) / 2;
    merge_sort(a, first, mid);
    merge_sort(a, mid + 1, last);

    for (i = first; i <= mid; i++) {
        tmp[i] = a[i];
    }
    for (i = mid + 1, j = last; i <= last; i++, j--) {
        tmp[i] = a[j];
    }

    i = first;
    j = last;

    for (k = first; k <= last; k++) {
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

/* クイックソート */
int pivot(int a[], int i, int j)
{
    int k = i + 1;
    while (k <= j && a[i] == a[k])
        k++;
    if (k > j)
        return -1;
    if (a[i] >= a[k])
        return i;
    return k;
}

int partition(int a[], int i, int j, int x)
{
    int l = i, r = j;

    while (l <= r) {
        while (l <= j && a[l] < x)
            l++;

        while (r >= i && a[r] >= x)
            r--;

        if (l > r)
            break;
        int t = a[l];
        a[l] = a[r];
        a[r] = t;
        l++;
        r--;
    }
    return l;
}

void quick_sort(int a[], int i, int j)
{
    if (i == j)
        return;
    int p = pivot(a, i, j);
    if (p != -1) {
        int k = partition(a, i, j, a[p]);
        quick_sort(a, i, k - 1);
        quick_sort(a, k, j);
    }
}

int main()
{
    mt.seed(seed_gen());
    cout << "count\tins\theap\tmerge\tquick\n";
    for (int i = 0; i <= 9; i++) {
        int count = 10000 * (i + 1);
        int loop = 1;
        int source[count];
        int a[count];
        cout << count << "\t";

        ifstream ifs;
        ifs.open("data/E" + to_string(i) + "a.txt");
        for (int i = 0; i < count; i++) {
            char buf[256];
            ifs.getline(buf, 256);
            source[i] = atoi(buf);
        }

        auto start = system_clock::now();
        auto end = system_clock::now();
        auto diff = end - start;
        auto microsec = duration_cast<microseconds>(diff).count();

        //// cout << "[ins]";
        start = system_clock::now();
        for (int l = 0; l < loop; l++) {
            memcpy(a, source, sizeof(source));
            insertion_sort(a, count);
        }
        end = system_clock::now();
        diff = end - start;
        microsec = duration_cast<microseconds>(diff).count();
        // cout << ((double)microsec / loop) << " micro sec";
        display_array(a, min(10, count));
        printf("%8.0f", (double)microsec / loop);

        // cout << "[heap]";
        start = system_clock::now();
        for (int l = 0; l < loop; l++) {
            memcpy(a, source, sizeof(source));
            heap_sort(a, count);
        }
        end = system_clock::now();
        diff = end - start;
        microsec = duration_cast<microseconds>(diff).count();
        // cout << ((double)microsec / loop) << " micro sec";
        display_array(a, min(10, count));
        printf("%8.0f", (double)microsec / loop);

        // cout << "[merge]";
        start = system_clock::now();
        for (int l = 0; l < loop; l++) {
            memcpy(a, source, sizeof(source));
            merge_sort(a, 0, count - 1);
        }
        end = system_clock::now();
        diff = end - start;
        microsec = duration_cast<microseconds>(diff).count();
        // cout << ((double)microsec / loop) << " micro sec";
        display_array(a, min(10, count));
        printf("%8.0f", (double)microsec / loop);

        // cout << "[quick]";
        start = system_clock::now();
        for (int l = 0; l < loop; l++) {
            memcpy(a, source, sizeof(source));
            quick_sort(a, 0, count - 1);
        }
        end = system_clock::now();
        diff = end - start;
        microsec = duration_cast<microseconds>(diff).count();
        // cout << ((double)microsec / loop) << " micro sec";
        display_array(a, min(10, count));
        printf("%8.0f\n", (double)microsec / loop);
    }

    return 0;
}