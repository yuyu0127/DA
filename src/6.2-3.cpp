#include <iostream>
#include <queue>
#include <vector>

using namespace std;

bool breadth_first_search(vector<vector<int>>& links, int start, int goal, int w, int h)
{
    /* 幅優先探索 */
    bool reachable = false; /* ゴールまで到達可能か */
    vector<int> from(w * h, -1); /* 各頂点がどこの頂点から探索されてきたか(-1で未探索) */
    queue<int> queue;

    from[start] = start;
    queue.push(start);
    while (!queue.empty()) {
        int vertex = queue.front();
        queue.pop();
        if (vertex == goal) {
            reachable = true;
            break;
        }
        for (int i = 0; i < links[vertex].size(); i++) {
            int vertex_next = links[vertex][i];
            if (from[vertex_next] == -1) {
                from[vertex_next] = vertex;
                queue.push(vertex_next);
            }
        }
    }

    /* 結果表示 */
    if (reachable) {
        cout << "(" << start % w << ", " << start / h << ") -> (" << goal % w << ", " << goal / h << ") : OK! ";

        vector<int> route_inv;
        route_inv.push_back(goal);
        int vertex = goal;
        while (vertex != start) {
            route_inv.push_back(from[vertex]);
            vertex = from[vertex];
        }
        cout << route_inv.size() - 1 << " steps (";
        for (int i = route_inv.size() - 1; i >= 0; i--) {
            cout << "(" << route_inv[i] % w << ", " << route_inv[i] / h << ")" << (i == 0 ? ")\n" : " -> ");
        }
    } else {
        cout << "(" << start % w << ", " << start / h << ") -> (" << goal % w << ", " << goal / h << ") : NG...\n";
    }

    return reachable;
}

int main(int argc, char const* argv[])
{
    int w, h;
    cin >> w >> h;

    vector<vector<int>> links(w * h, vector<int>()); /* 各マスから移動可能なマス */

    for (int i = 0; i < w * h; i++) {
        /*
            *にあるknightが移動可能範囲は+の部分
            . + . + .   -2
            + . . . +   -1
            . . * . .
            + . . . +   +1
            . + . + .   +2
            -2-10+1+2            
        */
        int x = i % w;
        int y = i / h;
        vector<int> mx = { -1, +1, -2, +2, -2, +2, -1, +1 };
        vector<int> my = { -2, -2, -1, -1, +1, +1, +2, +2 };
        for (int j = 0; j < mx.size(); j++) {
            if (0 <= x + mx[j] && x + mx[j] < w && 0 <= y + my[j] && y + my[j] < h) {
                links[i].push_back((y + my[j]) * h + (x + mx[j]));
            }
        }
        cout << i << " -> { ";
        for (auto l : links[i]) {
            cout << l << " ";
        }
        cout << "}\n";
    }

    vector<vector<bool>> reachable_list(w * h, vector<bool>(w * h, false));

    for (int start = 0; start < w * h; start++) {
        for (int goal = 0; goal < w * h; goal++) {
            reachable_list[start][goal] = breadth_first_search(links, start, goal, w, h);
        }
    }

    for (int s = 0; s < w * h; s++) {
        for (int g = 0; g < w * h; g++) {
            cout << (reachable_list[s][g] ? "o " : "x ");
        }
        cout << "\n";
    }

    return 0;
}
