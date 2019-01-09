#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

#define STACK_LENGTH 100

using namespace std;

class Stack {
private:
    int counter;
    double array[STACK_LENGTH];

public:
    Stack()
    {
        counter = 0;
    }

    void push(double num)
    {
        if (counter >= STACK_LENGTH) {
            throw "STACK OVERFLOW!";
        } else {
            array[counter++] = num;
        }
    }

    double pop()
    {
        if (counter <= 0) {
            throw "NOTHING TO POP!";
        }
        return array[--counter];
    }

    void print()
    {
        for (int i = 0; i < counter; i++) {
            cout << array[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    Stack stack;
    cout << "Enter the expression to calc(enter = to finish) : ";

    while (true) {
        string str;
        cin >> str;
        try {
            if (str == "+") {
                stack.push(stack.pop() + stack.pop());
            } else if (str == "-") {
                stack.push(-(stack.pop() - stack.pop()));
            } else if (str == "*") {
                stack.push(stack.pop() * stack.pop());
            } else if (str == "/") {
                stack.push((1 / stack.pop()) * stack.pop());
            } else if (str != "=") {
                stack.push(stod(str));
            } else {
                stack.print();
                return 0;
            }
            stack.print();
        } catch (...) {
            cout << "Invalid expression!" << endl;
            return -1;
        }
    }

    return 0;
}