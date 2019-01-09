#include <iostream>
#define STACK_LENGTH 10 /* スタックに格納できる数値の最大個数 */
using namespace std;

class Stack {
private:
    int counter; /* 現在スタックに格納されている数値の個数 */
    int array[STACK_LENGTH]; /* 数値を格納する配列 */

public:
    /* コンストラクタ */
    Stack()
    {
        /* counterを0で初期化 */
        counter = 0;
    }

    void push(int num)
    {
        if (counter >= STACK_LENGTH) {
            throw "[ERROR]STACK OVERFLOW!";
        } else {
            array[counter++] = num;
        }
    }

    int pop()
    {
        if (counter <= 0) {
            throw "[ERROR]NOTHING TO POP!";
        }
        return array[--counter];
    }
};

int main()
{
    Stack stack;

    while (true) {
        char command;
        cout << "Enter the command (push=a pop=p quit=q) : ";
        cin >> command;

        switch (command) {
        case 'a':
            int num;
            cout << "Enter the value to push : ";
            cin >> num;
            try {
                stack.push(num);
            } catch (char const* str) {
                cout << str << endl;
            }
            break;

        case 'p':
            try {
                cout << stack.pop() << endl;
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