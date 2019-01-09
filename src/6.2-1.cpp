#include <iostream>
#include <stack>
#include <vector>
using namespace std;

void depth_first_search(vector<vector<int>>& links, int start, int goal)
{
    bool reachable = false;
    vector<int> from(links.size(), -1);
    stack<int> stack_vertex;

    from[start] = start;
    stack_vertex.push(start);
    while (!stack_vertex.empty()) {
        int vertex = stack_vertex.top();
        stack_vertex.pop();
        if (vertex == goal) {
            reachable = true;
            break;
        }
        for (int i = 0; i < links[vertex].size(); i++) {
            int vertex_next = links[vertex][i];
            if (from[vertex_next] == -1) {
                from[vertex_next] = vertex;
                stack_vertex.push(vertex_next);
            }
        }
    }

    /* 結果表示 */
    if (reachable) {
        cout << start << " -> " << goal << " : OK! ";

        vector<int> route_inv;
        route_inv.push_back(goal);

        int vertex = goal;
        while (vertex != start) {
            route_inv.push_back(from[vertex]);
            vertex = from[vertex];
        }

        cout << route_inv.size() - 1 << " steps (";
        for (int i = route_inv.size() - 1; i >= 0; i--) {
            cout << route_inv[i] << (i == 0 ? ")\n" : " -> ");
        }
    } else {
        cout << start << " -> " << goal << " : NG...\n";
    }
}

int main(int argc, char const* argv[])
{
    int vertex_count; /* 頂点数 */

    /* 隣接行列を入力させて隣接リストを生成する */
    cout << "number of vertexs? ";
    cin >> vertex_count;

    vector<vector<int>> links(vertex_count, vector<int>()); /* 各頂点の隣接リスト */

    cout << "adjacency matrix?\n";
    for (int y = 0; y < vertex_count; y++) {
        for (int x = 0; x < vertex_count; x++) {
            int n = 0;
            cin >> n;
            if (n == 1) {
                links[y].push_back(x);
            }
        }
    }

    /* 隣接リストを表示する */
    cout << "\n[adjacency list]\n";
    for (int i = 0; i < vertex_count; i++) {
        cout << i << " -> { ";
        for (int j = 0; j < links[i].size(); j++) {
            cout << links[i][j] << " ";
        }
        cout << "}\n";
    }

    /* 全ての頂点の組み合わせに対して探索を行う */
    cout << "\n[reachability]\n";
    for (int start = 0; start < vertex_count; start++) {
        for (int goal = 0; goal < vertex_count; goal++) {
            depth_first_search(links, start, goal);
        }
    }

    return 0;
}
