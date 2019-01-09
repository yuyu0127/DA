#include <iostream>
using namespace std;

class SinglyLinkedList {
private:
    struct Node {
        int value;
        Node* next;
    };

    Node* dummy; /* 終端の次にいる番兵みたいなの */

public:
    SinglyLinkedList()
    {
        dummy = new Node();
        dummy->next = dummy; /* dummyの次の要素はdummy自身としておく(色々と都合がいいので) */
    }

    Node* insert_at(int position, int value)
    {
        Node* nodeptr = dummy;
        if (position <= -1) {
            return nullptr;
        }
        for (int i = 0; i < position; i++) {
            if (nodeptr->next == dummy) {
                return nullptr;
            }
            nodeptr = nodeptr->next;
        }
        Node* new_node = new Node();
        new_node->value = value;
        new_node->next = nodeptr->next;
        nodeptr->next = new_node;
        return new_node;
    }
    /*
    
    list      0 1 2 3 4 5 6
             ^ ^ ^ ^ ^ ^ ^ ^
    position 0 1 2 3 4 5 6 7
    positionの範囲は 0～リストの要素数

    やってること：
    nodeptrをdummyのアドレスで初期化
    positionが-1以下の時はnullptrを返す
    以下でposition回ループを回す：
        nodeptrの次がdummy、つまり「nodeptrが終端を指している」場合、nullptrを返す
        そうでなければ、nodeptrを1つ後方にずらす

    [ここまでの処理は「0 <= position <= リストの要素数」が成り立っているかを調べるような処理
     この段階で「入れるべき場所に本当に入れられるか」が分かっている（入れられなければnullptrが返っている）
     また、このときのnodeptrは「入れるべき場所の前のノードのアドレス」が入っている]

    new_nodeを新たに作成
    new_nodeの次のノードは，nodeptrの次のノードとする
        [つまり
            X -> nodeptr -> Y
         から
            X -> nodeptr -> Y
            new_node -> Y
         の状態にする]
    nodeptrの次のノードは，new_nodeとする
        [つまり
            X -> nodeptr -> Y
            new_node -> Y
         から
            X -> nodeptr -> new_node
            new_node -> Y
         の状態にする]
    [これで
        X -> nodeptr -> new_node -> Y
     となる]
    new_nodeのアドレスを返して終了
    */

    Node* delete_value(int value)
    {
        Node* nodeptr = dummy;
        while (true) {
            if (nodeptr->next != dummy && nodeptr->next->value == value) {
                Node* delptr = nodeptr->next;
                nodeptr->next = nodeptr->next->next;
                delete delptr;
                return nodeptr;
            }
            nodeptr = nodeptr->next;
            if (nodeptr == dummy) {
                return nullptr;
            }
        }
    }

    /*  
    nodeptrをdummyとする
    以下を繰り返す：
        もし
         nodeptr->next != dummy つまり 「nodeptrは終端ではない」
        かつ
         nodeptr->next->value == value つまり 「nodeptrの次が消したい要素である」
        ならば：
            delptr は nodeptrの次の要素とし、
            nodeptrの次の要素はnodeptrの次の次の要素とする
                [nodeptr -> A -> B
                 となっていた場合、
                 delptr = A
                 として、
                 nodeptr -> B
                 に書き換える]
            delptrをメモリから解放
            nodeptr(消した要素の前方の要素のアドレス)を返す

        そうでなければ(elseはないが、上の条件を満たす場合returnで強制的に関数から抜け出しているはず)：
            nodeptrを1つ後方にずらす
            この段階でnodeptrが終端になっていた場合、nullptrを返す
    */

    Node* search_value(int value)
    {
        Node* nodeptr = dummy;
        while (true) {
            if (nodeptr != dummy && nodeptr->value == value) {
                return nodeptr;
            }
            nodeptr = nodeptr->next;
            if (nodeptr == dummy) {
                return nullptr;
            }
        }
    }

    void print()
    {
        Node* nodeptr = dummy;
        while (true) {
            nodeptr = nodeptr->next;
            if (nodeptr == dummy) {
                break;
            }
            cout << nodeptr->value << " (" << nodeptr << ")\n";
        }
    }
};

int main(int argc, char const* argv[])
{
    SinglyLinkedList list = SinglyLinkedList();

    while (true) {
        list.print();
        char command;
        int value;
        cout << "Enter the command (i=insert d=delete s=search q=quit) : ";
        cin >> command;

        switch (command) {

        case 'i': {
            cout << "Enter the position and value to insert : ";
            int position;
            cin >> position >> value;
            auto nodeptr = list.insert_at(position, value);
            if (nodeptr != nullptr) {
                cout << "Inserted :" << nodeptr << "\n";
            } else {
                cout << "Insert Failed\n";
            }
            break;
        }

        case 'd': {
            cout << "Enter the value to delete : ";
            cin >> value;
            auto nodeptr = list.delete_value(value);
            if (nodeptr != nullptr) {
                cout << "Found\n";
            } else {
                cout << "Not Found\n";
            }
            break;
        }

        case 's': {
            cout << "Enter the value to search : ";
            cin >> value;
            auto nodeptr = list.search_value(value);
            if (nodeptr != nullptr) {
                cout << "Found : " << nodeptr << "\n";
            } else {
                cout << "Not Found\n";
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
