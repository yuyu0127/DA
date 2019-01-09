#include <iostream>
using namespace std;

class DoublyLinkedList {
private:
    struct Node {
    public:
        int value;
        Node* prev;
        Node* next;
    };
    Node* dummy;

public:
    int size;

    DoublyLinkedList()
    {
        dummy = new Node();
        dummy->prev = dummy;
        dummy->next = dummy;
        size = 0;
    }

    Node* insert_at(int index, int value)
    {
        Node* node_ptr = dummy;
        while (index--) {
            node_ptr = node_ptr->next;
            if (node_ptr == dummy) {
                throw "Error : Index out of range";
            }
        }
        Node* new_node = new Node();

        new_node->value = value;
        new_node->prev = node_ptr;
        new_node->next = node_ptr->next;

        node_ptr->next->prev = new_node;
        node_ptr->next = new_node;

        size++;
        return new_node;
    }

    int delete_at(int index)
    {
        if (size == 0) {
            throw "Error : Index out of range";
        }
        
        index++;
        Node* node_ptr = dummy;
        while (index--) {
            node_ptr = node_ptr->next;
            if (node_ptr == dummy) {
                throw "Error : Index out of range";
            }
        }
        int value = node_ptr->value;

        node_ptr->next->prev = node_ptr->prev;
        node_ptr->prev->next = node_ptr->next;

        delete node_ptr;
        size--;
        return value;
    }

    void print_node()
    {
        for (Node* node_ptr = dummy->next; node_ptr != dummy; node_ptr = node_ptr->next) {
            cout << node_ptr->value << " [address:" << node_ptr << "]\n";
        }
    }
};

class Stack {
private:
    DoublyLinkedList list;

public:
    Stack()
    {
        list = DoublyLinkedList();
    }

    void push(int value)
    {
        list.insert_at(0, value);
        list.print_node();
    }

    int pop()
    {

        try {
            return list.delete_at(0);
        } catch (const char* str) {
            throw str;
        }
    }
};

int main(int argc, char const* argv[])
{
    Stack stack = Stack();

    while (true) {
        char command;
        int value;
        cout << "Enter the command (a=push p=pop q=quit) : ";
        cin >> command;

        switch (command) {
        case 'a': {
            cout << "Enter the value to push : ";
            cin >> value;
            stack.push(value);
            break;
        }
        case 'p': {
            try {
                cout << stack.pop() << endl;
            } catch (const char* str) {
                cout << "[Error]Stack Empty!\n";
            }
            break;
        }
        case 'q': {
            return 0;
        }

        default:
            break;
        }
    }
    return 0;
}
