#include <iostream>
#define STACK_LENGTH 100
using namespace std;

int hand_count = 1;

class Stack {
private:
    int counter;
    int array[STACK_LENGTH];

public:
    Stack()
    {
        counter = 0;
    }

    void push(int num)
    {
        if (counter >= STACK_LENGTH) {
            throw "STACK OVERFLOW!";
        } else {
            array[counter++] = num;
        }
    }

    int pop()
    {
        if (counter <= 0) {
            throw "NOTHING TO POP!";
        }
        return array[--counter];
    }

    void print()
    {
        for (int i = 0; i < counter; i++) {
            cout << array[i];
        }
        cout << endl;
    }
};

void move_hanoi(Stack* a, Stack* b, Stack* c, Stack* from, Stack* spare, Stack* to, const int count)
{
    if (count > 0) {
        /* from にある円盤を、一番下以外 spare に移動させる */
        move_hanoi(a, b, c, from, to, spare, count - 1);

        try {
            /* 現在の様子と手数を表示 */
            cout << " A ";
            a->print();
            cout << " B ";
            b->print();
            cout << " C ";
            c->print();
            cout << (hand_count++) << endl;

            /* from に一枚だけ残っている円盤を to に移動させる */
            to->push(from->pop());
            /* これで from から円盤がなくなる */

        } catch (const char* str) {
            cout << str << endl;
        }

        /* この段階で全ての円盤は spare に移動した */
        /* spare にある円盤を全て to に移動させる */
        move_hanoi(a, b, c, spare, from, to, count - 1);
    }
}

int main()
{
    int count;
    Stack a; /* ハノイの塔の棒A */
    Stack b; /* ハノイの塔の棒B */
    Stack c; /* ハノイの塔の棒C */

    cout << "Enter the height of Tower of Hanoi : ";
    cin >> count;

    /* 棒Aにcount枚の円盤を乗せる */
    for (int i = count; i > 0; i--) {
        a.push(i);
    }

    /* 棒Aから棒Cに全ての円盤を動かす */
    move_hanoi(&a, &b, &c, &a, &b, &c, count);

    /* 最終状態を表示する */
    cout << " A ";
    a.print();
    cout << " B ";
    b.print();
    cout << " C ";
    c.print();
    cout << "Finish!" << endl;

    return 0;
}