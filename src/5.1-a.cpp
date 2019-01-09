#include <iostream>
#include <string>
#define HASH_SIZE 701

class SinglyLinkedList {
private:
    struct Node {
    public:
        std::string value;
        Node* next;
    };
    Node* head;

public:
    SinglyLinkedList()
    {
        head = nullptr;
    }

    Node* insert_first(std::string value)
    {
        /* ノードがない場合 */
        if (head == nullptr) {
            Node* new_node = new Node();
            new_node->value = value;
            new_node->next = nullptr;
            head = new_node;
            return new_node;
        }

        Node* new_node = new Node();
        new_node->value = value;
        new_node->next = head;
        head = new_node;
        return new_node;
    }

    void remove(std::string value)
    {
        Node* node_ptr = head;
        Node* node_prev_ptr = nullptr;
        while (true) {
            /* そもそもノードがない場合例外を吐く */
            if (node_ptr == nullptr) {
                throw "Error : List is empty";
            }

            /* 参照中の値が消したい値と一致していたらそのノードを消す */
            if (node_ptr->value == value) {
                if (node_ptr == head) {
                    head = node_ptr->next;
                } else {
                    node_prev_ptr->next = node_ptr->next;
                }
                delete node_ptr;
                return;
            }

            /* 最後のノードまで行き着いたら消す値がないということで例外を吐く */
            if (node_ptr->next == nullptr) {
                throw "Error : Value does not exist in the list";
            }

            node_prev_ptr = node_ptr;
            node_ptr = node_ptr->next;
        }
    }

    Node* search(std::string value)
    {
        /* リストが空であればnullptrを返す */
        if (head == nullptr) {
            return nullptr;
        }

        /* ノードを辿る */
        for (Node* node_ptr = head; node_ptr != nullptr; node_ptr = node_ptr->next) {
            if (node_ptr->value == value) {
                return node_ptr;
            }
        }
        return nullptr;
    }

    void print()
    {
        if (head == nullptr) {
            std::cout << "No node" << std::endl;
            return;
        }

        for (Node* node_ptr = head; node_ptr != nullptr; node_ptr = node_ptr->next) {
            std::cout << node_ptr->value << " ";
        }
        std::cout << std::endl;
    }
};

int cahc_hash(std::string str)
{
    int hash_num = 0;
    for (int i = 0; i < str.size(); i++) {
        hash_num += ((int)str[str.size() - i - 1] * (1 << i)) % HASH_SIZE;
        hash_num %= HASH_SIZE;
    }
    return hash_num;
}

int main(int argc, char const* argv[])
{
    SinglyLinkedList lists[HASH_SIZE];
    for (int i = 0; i < HASH_SIZE; i++) {
        lists[i] = SinglyLinkedList();
    }

    while (true) {
        char command;
        std::cout << "command? (a=add r=remove s=search q=quit) : ";
        std::cin >> command;

        switch (command) {
        case 'a': {
            std::string str;
            std::cout << "string to add? : ";
            std::cin >> str;
            int hash_num = cahc_hash(str);
            std::cout << "hash=" << hash_num << "\n";

            lists[hash_num].insert_first(str);
            break;
        }

        case 'r': {
            std::string str;
            std::cout << "string to remove? : ";
            std::cin >> str;
            int hash_num = cahc_hash(str);
            std::cout << "hash=" << hash_num << "\n";
            try {
                lists[hash_num].remove(str);
                std::cout << "Remove succeed!\n";
            } catch (const char* str) {
                std::cout << "Not found\n";
            }
            break;
        }

        case 's': {
            std::string str;
            std::cout << "string to search? : ";
            std::cin >> str;
            int hash_num = cahc_hash(str);
            std::cout << "hash=" << hash_num << "\n";
            auto node_ptr = lists[hash_num].search(str);
            if (node_ptr != nullptr) {
                std::cout << "Found!\n";
            } else {
                std::cout << "Not found\n";
            }
            break;
        }

        case 'q': {
            return 0;
        }

        default:
            break;
        }

        std::cout << "\n";
    }

    return 0;
}
