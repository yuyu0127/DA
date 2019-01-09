/* cf https://dencity.jp/misc/graph/ */

#include <iostream>
#include <random>
#include <time.h>
#include <vector>

using namespace std;

struct edge {
    int vertex1, vertex2;

    edge(int v1, int v2)
    {
        vertex1 = v1;
        vertex2 = v2;
    }
};

void build_ba_model(int init_vertex, int max_vertex)
{

    mt19937 mt((unsigned)time(NULL));

    int vertex_count = 0;
    vector<edge> edges;

    for (int i = 0; i < init_vertex; i++) {
        vertex_count++;
        for (int j = i; j < init_vertex; j++) {
            if (i != j) {
                edges.push_back(edge(i, j));
            }
        }
    }

    for (int i = init_vertex; i < max_vertex; i++) {
        edge e = edges[mt() % edges.size()]; /* 辺を1つ選択 */
        int vertex_id = (mt() % 2 == 0 ? e.vertex1 : e.vertex2); /* この頂点に延ばす */
        edges.push_back(edge(vertex_count, vertex_id));
        vertex_count++;
    }

    vector<vector<int>> edges_list(max_vertex);

    for (auto e : edges) {
        edges_list[e.vertex1].push_back(e.vertex2);
        edges_list[e.vertex2].push_back(e.vertex1);
    }

    /* 接続リストを出力 */
    /*
    for (int i = 0; i < edges_list.size(); i++) {
        cout << i << " -> { ";
        for (int j = 0; j < edges_list[i].size(); j++) {
            cout << edges_list[i][j] << " ";
        }
        cout << "}\n";
    }

    vector<vector<int>> matrix(max_vertex, vector<int>(max_vertex, 0));
    for (auto edge : edges) {
        matrix[edge.vertex1][edge.vertex2] = 1;
        matrix[edge.vertex2][edge.vertex1] = 1;
    }
    for (int i = 0; i < max_vertex; i++) {
        for (int j = 0; j < max_vertex; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
    */

    vector<int> edges_count(max_vertex, 0);
    /* i番目は，出ている辺がi個であるようなノードの個数 */
    for (int i = 0; i < edges_count.size(); i++) {
        edges_count[edges_list[i].size()]++;
    }
    cout << "x_" << init_vertex << "_" << max_vertex << " = [";
    for (int i = 0; i < edges_count.size(); i++) {
        if (edges_count[i] != 0) {
            cout << i << ", ";
        }
    }
    cout << char(8) << char(8) << "]\n";
    cout << "y_" << init_vertex << "_" << max_vertex << " = [";
    for (int i = 0; i < edges_count.size(); i++) {
        if (edges_count[i] != 0) {
            cout << edges_count[i] << ", ";
        }
    }
    cout << char(8) << char(8) << "]\n";
}

int main(int argc, char const* argv[])
{
    build_ba_model(2, 10);
    build_ba_model(2, 100);
    build_ba_model(2, 1000);
    build_ba_model(2, 10000);
    build_ba_model(2, 100000);
    build_ba_model(2, 1000000);
    build_ba_model(2, 10000000);

    return 0;
}
