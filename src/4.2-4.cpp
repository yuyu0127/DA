#include <iostream>
using namespace std;

class Tree {
private:
    struct Node {
        int value;
        Node* parent;
        Node* left;
        Node* right;

        Node(int _value, Node* _parent)
        {
            value = _value;
            parent = _parent;
            left = nullptr;
            right = nullptr;
        }
    };
    Node* root;

    void print_sub(Node* node, int indent, bool is_left)
    {
        /* 左の木を表示 */
        if (node->left != nullptr) {
            print_sub(node->left, indent + 1, true);
        }

        /* 現在のノードの値を表示 */
        for (int i = 0; i <= indent; i++) {
            cout << (i < indent ? "        " : "+-------");
        }
        cout << node->value << "(" << (is_left ? "L" : "R") << ":" << node << ")\n";

        /* 右の木を表示 */
        if (node->right != nullptr) {
            print_sub(node->right, indent + 1, false);
        }
    }

public:
    Tree()
    {
        root = nullptr;
    }

    Node* insert(int value)
    {
        if (root == nullptr) {
            root = new Node(value, nullptr);
            return root;
        }

        Node* node = root;
        Node* parent_ptr = nullptr;
        while (node != nullptr) {
            parent_ptr = node;
            if (node->value < value) {
                node = node->right;
            } else {
                node = node->left;
            }
        }

        node = new Node(value, parent_ptr);
        if (parent_ptr->value < value) {
            parent_ptr->right = node;
        } else {
            parent_ptr->left = node;
        }

        return node;
    }

    Node* search(int value)
    {
        Node* node = root;
        while (node != nullptr) {
            if (node->value == value) {
                return node;
            }

            if (node->value < value) {
                node = node->right;
            } else {
                node = node->left;
            }
        }
        return nullptr;
    }

    bool remove(int value)
    {
        Node* node = root;
        while (node != nullptr) {
            if (node->value == value) {
                /* 削除対象の値が見つかったとき */
                bool has_left = (node->left != nullptr);
                bool has_right = (node->right != nullptr);

                if (!has_left && !has_right) {
                    /* 子を1つも持たないとき */
                    if (node == root) {
                        /* 自身がrootであればrootを削除 */
                        root = nullptr;
                    } else {
                        /* 自身がrootでないとき */
                        if (node->parent->left == node) {
                            /* 自分が左側の子のとき */
                            node->parent->left = nullptr;
                        } else {
                            /* 自分が右側の子のとき */
                            node->parent->right = nullptr;
                        }
                    }

                } else if (has_left && !has_right) {
                    /* 左の子だけ持つとき */
                    if (node == root) {
                        /* 自身がrootであれば，左の子にrootを譲り，親をnullにする */
                        root = node->left;
                        root->parent = nullptr;
                    } else {
                        /* 自身がrootでないとき */
                        if (node->parent->left == node) {
                            /* 自分が左側の子のとき */
                            node->parent->left = node->left;
                        } else {
                            /* 自分が右側の子のとき */
                            node->parent->right = node->left;
                        }
                        node->left->parent = node->parent;
                    }

                } else if (!has_left && has_right) {
                    /* 右の子だけ持つとき */
                    if (node == root) {
                        /* 自身がrootであれば，左の子にrootを譲り，親をnullにする */
                        root = node->right;
                        root->parent = nullptr;
                    } else {
                        /* 自身がrootでないとき */
                        if (node->parent->left == node) {
                            /* 自分が左側の子のとき */
                            node->parent->left = node->right;
                        } else {
                            /* 自分が右側の子のとき */
                            node->parent->right = node->right;
                        }
                        node->right->parent = node->parent;
                    }

                } else {
                    /* 両方の子を持つとき */
                    Node* tmp = node->left;
                    while (tmp->right != nullptr) {
                        tmp = tmp->right;
                    }
                    /* tmpは交換対象 */

                    node->value = tmp->value;
                    if (tmp->parent->left == tmp) {
                        /* 交換対象が左側の子のとき */
                        tmp->parent->left = nullptr;
                    } else {
                        /* 交換対象が右側の子のとき */
                        tmp->parent->right = nullptr;
                    }

                    node = tmp;
                }

                delete node;
                return true;
            }

            if (node->value < value) {
                node = node->right;
            } else {
                node = node->left;
            }
        }

        return false;
    }

    ~Tree()
    {
    }

    void print()
    {
        cout << "\n[Tree]\n";
        if (root == nullptr) {
            cout << "No nodes\n";
            return;
        }
        print_sub(root, 0, true);
        cout << "\n";
    }
};

int main(int argc, char const* argv[])
{
    Tree tree = Tree();

    while (true) {
        char command;
        int value;
        cout << "command? (i=insert d=delete s=search q=quit) : ";
        cin >> command;

        switch (command) {
        case 'i': {
            cout << "value? : ";
            cin >> value;
            tree.insert(value);
            break;
        }

        case 'd': {
            cout << "value? : ";
            cin >> value;
            if (tree.remove(value)) {
                cout << "Delete succeeded\n";
            } else {
                cout << "Not Found\n";
            }
            break;
        }

        case 's': {
            cout << "value? : ";
            cin >> value;
            auto node = tree.search(value);
            if (node == nullptr) {
                cout << "Not Found\n";
            } else {
                cout << "Found [" << node << "]\n";
            }
            break;
        }

        case 'q': {
            return 0;
        }

        default:
            break;
        }

        tree.print();
    }
    return 0;
}
