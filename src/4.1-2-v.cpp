#include <iostream>
#define QUEUE_LENGTH 10
using namespace std;

class Queue {
private:
    int head;
    int tail;
    int count;
    int array[QUEUE_LENGTH];

public:
    Queue()
    {
        head = 0;
        tail = 0;
        count = 0;

#pragma region 不要
        for (int i = 0; i < QUEUE_LENGTH; i++) {
            array[i] = 0;
        }

        /* ↓ 中身の表示 ↓ */
        for (int i = 0; i < QUEUE_LENGTH; i++) {
            if (i == head % QUEUE_LENGTH) {
                printf("[ ");
            }
            if (i == tail % QUEUE_LENGTH) {
                printf("] ");
            }
            if (array[i] == 0) {

                printf("- ", array[i]);
            } else {
                printf("%d ", array[i]);
            }
        }
        printf("\n");
/* ↑ 中身の表示 ↑ */
#pragma endregion
    }

    void enqueue(int num)
    {
        if (count >= QUEUE_LENGTH) {
            throw "[ERROR]QUEUE OVERFLOW!";
        }
        count++;
        array[(tail++) % QUEUE_LENGTH] = num;

#pragma region 不要

        /* ↓ 中身の表示 ↓ */
        for (int i = 0; i < QUEUE_LENGTH; i++) {
            if (i == tail % QUEUE_LENGTH) {
                printf("] ");
            }
            if (i == head % QUEUE_LENGTH) {
                printf("[ ");
            }
            if (array[i] == 0) {

                printf("- ", array[i]);
            } else {
                printf("%d ", array[i]);
            }
        }
        printf("\n");
/* ↑ 中身の表示 ↑ */
#pragma endregion
    }

    int dequeue()
    {
        if (count <= 0) {
            throw "[ERROR]NO QUEUE LEFT!";
        }
        count--;
        int x = array[head % QUEUE_LENGTH];
        head++;

#pragma region 不要

        /* ↓ 中身の表示 ↓ */
        for (int i = 0; i < QUEUE_LENGTH; i++) {
            if (i == head % QUEUE_LENGTH) {
                printf("[ ");
            }
            if (i == tail % QUEUE_LENGTH) {
                printf("] ");
            }
            if (array[i] == 0) {
                printf("- ", array[i]);
            } else {
                printf("%d ", array[i]);
            }
        }
        printf("\n");
/* ↑ 中身の表示 ↑ */
#pragma endregion

        return x;
    }
};

int main()
{
    Queue queue;

    while (true) {
        char command;
        cout << "-command? ";
        cin >> command;

        switch (command) {
        case 'e':
            int num;
            cout << "--value? ";
            cin >> num;
            try {
                queue.enqueue(num);
            } catch (char const* str) {
                cout << str << endl;
            }
            break;

        case 'd':
            try {
                cout << queue.dequeue() << endl;
            } catch (char const* str) {
                cout << str << endl;
            }
            break;

        case 'q':
            return 0;

        default:
            continue;
        }
    }

    return 0;
}