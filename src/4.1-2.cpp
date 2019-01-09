#include <iostream>
#define QUEUE_LENGTH 10
using namespace std;

class Queue {
private:
    int head;
    int tail;
    int array[QUEUE_LENGTH];

public:
    Queue()
    {
        head = 0;
        tail = 0;
    }

    void enqueue(int num)
    {
        if (tail - head >= QUEUE_LENGTH) {
            throw "[ERROR]QUEUE OVERFLOW!";
        }
        array[(tail++) % QUEUE_LENGTH] = num;
    }

    int dequeue()
    {
        if (tail - head <= 0) {
            throw "[ERROR]NO QUEUE LEFT!";
        }
        return array[(head++) % QUEUE_LENGTH];
    }
};

int main()
{
    Queue queue;

    while (true) {
        char command;
        cout << "Enter the command (enqueue=e dequeue=d quit=q) : ";
        cin >> command;

        switch (command) {
        case 'e':
            int num;
            cout << "Enter the value to enqueue : ";
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