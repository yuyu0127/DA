#include <chrono>
#include <iostream>
#include <vector>

using namespace std;
typedef unsigned long long ull;

static ull cnt = 0;

struct Node {
    int idx;
    vector<Node*> neighbors;
    bool is_visited;
    bool is_goal;

    Node(int idx)
        : idx(idx)
        , is_visited(false)
        , is_goal(false)
    {
    }

    void Count()
    {
        if (is_goal) {
            cnt++;
            return;
        }
        is_visited = true;
        for (auto p = neighbors.begin(); p != neighbors.end(); ++p) {
            if (!(*p)->is_visited) {
                (*p)->Count();
            }
        }
        is_visited = false;
    }
};

int main(int argc, char const* argv[])
{
    int N; /* マスの数 = N*N */
    vector<Node*> nodes;
    cin >> N;

    for (int i = 0; i < N * N; i++) {
        nodes.push_back(new Node(i));
    }
    nodes[N * N - 1]->is_goal = true;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int x = i * N + j; /* (i, j) */
            if (x - N >= 0) {
                /* 一番上の行ではない場合，1つ上のマスは到達可能 */
                nodes[x]->neighbors.push_back(nodes[x - N]);
            }
            if (x + N < N * N) {
                /* 一番下の行ではない場合，1つ下のマスは到達可能 */
                nodes[x]->neighbors.push_back(nodes[x + N]);
            }
            if (x % N != 0) {
                /* 一番左の行ではない場合，1つ左のマスは到達可能 */
                nodes[x]->neighbors.push_back(nodes[x - 1]);
            }
            if (x % N != N - 1) {
                /* 一番右の行ではない場合，1つ右のマスは到達可能 */
                nodes[x]->neighbors.push_back(nodes[x + 1]);
            }
        }
    }

    nodes[0]->Count();

    cout << cnt << "\n";

    return 0;
}
