#include <iostream>
#include <limits>
using namespace std;

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

    int max = numeric_limits<int>::min();
    int min = numeric_limits<int>::max();
    for (int i = 0; i < count; i++) {
        max = array[i] > max ? array[i] : max;
        min = array[i] < min ? array[i] : min;
    }

    cout << "Min : " << min << endl;
    cout << "Max : " << max << endl;

    return 0;
}