#include <iostream>
using namespace std;

class DoublyLinkedList {
public:
    struct Node {
    public:
        int value;
        Node* prev;
        Node* next;
    };

private:
    Node* dummy; /* 番兵みたいなやつ */

public:
    DoublyLinkedList()
    {
        dummy = new Node();
        dummy->prev = dummy;
        dummy->next = dummy;
        /* ...- dummy - dummy - dummy - dummy -... みたいな状況になってる */
    }

    /* 最初のノードはdummyの次、最後のノードはdummyの前ということにする */
    Node* first() { return dummy->next; }
    Node* last() { return dummy->prev; }

    /*
    insert_node
    指定の位置に要素を挿入する

    list      0 1 2 3 4
             ^ ^ ^ ^ ^ ^
    position 0 1 2 3 4 5
    */
    Node* insert_node(int position, int value)
    {
        if (position < 0) {
            /* positionは0以上でなければならない */
            throw "[Error]Position out of range";
        }

        Node* nodeptr = dummy;
        for (int i = 0; i < position; i++) {
            /* posision回辿っていく */
            nodeptr = nodeptr->next;
            if (nodeptr == dummy) {
                /* その間に最後に行き着いたらエラー(positionがサイズを超えちゃうので) */
                throw "[Error]Position out of range";
            }
        }

        Node* new_node = new Node(); /* 新たに挿入する要素 */
        /*
        dummy A B dummy
               ^ ここに挿入したい場合を考える
        */
        new_node->value = value;
        new_node->prev = nodeptr;
        /* A <- new_node となる */
        new_node->next = nodeptr->next;
        /* A <- new_node -> B となる */
        nodeptr->next->prev = new_node;
        /* A <- new_node <-> B となる */
        nodeptr->next = new_node;
        /* A <-> new_node <-> B となる */
        return new_node;
    }

    /*
    delete_node
    指定した値を持つ要素をリストから削除する
    */
    void delete_node(int value)
    {
        /* 最初の要素から始まり、最後の要素を通過してしまうまで、要素を辿る */
        for (Node* nodeptr = dummy->next; nodeptr != dummy; nodeptr = nodeptr->next) {
            if (nodeptr->value == value) {
                /* 指定した値が見つかった場合 */
                /* dummy A B C dummy として、Bを削除したいときを考える */
                nodeptr->prev->next = nodeptr->next;
                /* A -> C となる */
                nodeptr->next->prev = nodeptr->prev;
                /* A <-> C となる */
                delete nodeptr; /* 孤立したBをメモリから解放 */
                return;
            }
        }
        /* 最後まで値が見つからなかった場合、エラー */
        throw "[Error]Value does not exist in the list";
    }

    Node* search_node(int value)
    {
        /* 最初の要素から始まり、最後の要素を通過してしまうまで、要素を辿る */
        for (Node* nodeptr = dummy->next; nodeptr != dummy; nodeptr = nodeptr->next) {
            if (nodeptr->value == value) {
                /* 指定した値が見つかった場合、その要素のアドレスを返す */
                return nodeptr;
            }
        }
        /* 最後まで値が見つからなかった場合、nullptrを返す */
        return nullptr;
    }

    void print_node()
    {
        cout << "SENTINEL : " << dummy << "\n";
        for (Node* nodeptr = dummy->next; nodeptr != dummy; nodeptr = nodeptr->next) {
            cout << nodeptr->value << " [";
            if (nodeptr->prev == dummy) {
                cout << "SENTINEL";
            } else {
                cout << nodeptr->prev;
            }
            cout << " < ";
            if (nodeptr == dummy) {
                cout << "SENTINEL";
            } else {
                cout << nodeptr;
            }
            cout << " > ";
            if (nodeptr->next == dummy) {
                cout << "SENTINEL";
            } else {
                cout << nodeptr->next;
            }
            cout << "]\n";
        }
    }
};

int main(int argc, char const* argv[])
{
    DoublyLinkedList list = DoublyLinkedList();

    while (true) {
        char command;
        int value;
        cout << "Enter the command (i=insert d=delete s=search q=quit) : ";
        cin >> command;

        switch (command) {
        case 'i': {
            cout << "Enter the position and value to insert : ";
            int position;
            cin >> position >> value;
            try {
                list.insert_node(position, value);
            } catch (const char* str) {
                cout << str << endl;
            }
            list.print_node();
            break;
        }

        case 'd': {
            cout << "Enter the value to delete : ";
            cin >> value;
            try {
                list.delete_node(value);
            } catch (const char* str) {
                cout << str << endl;
            }
            list.print_node();
            break;
        }

        case 's': {
            cout << "Enter the value to search : ";
            cin >> value;
            DoublyLinkedList::Node* found_nodeptr = list.search_node(value);
            if (found_nodeptr == nullptr) {
                cout << "Not found" << endl;
            } else {
                cout << "Found [address:" << found_nodeptr << "]" << endl;
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
