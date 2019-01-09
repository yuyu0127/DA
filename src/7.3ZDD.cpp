#include <algorithm>
#include <bitset>
#include <chrono>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

constexpr auto ARRAY_SIZE = 100;
using namespace std;

typedef pair<int, int> pii;
typedef unordered_map<int, int> mii;

class GridGraph {
public:
    int N;
    vector<pii> edges;
    int N_vertex;

    GridGraph()
        : N(0)
        , edges(vector<pii>())
        , N_vertex(0)
    {
    }

    GridGraph(int _N)
        : N(_N)
        , edges(vector<pii>())
        , N_vertex((N + 1) * (N + 1))
    {
        int vertex_counter = 1;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < i + 1; j++) {
                edges.push_back(make_pair(vertex_counter, vertex_counter + i + 1));
                edges.push_back(make_pair(vertex_counter, vertex_counter + i + 2));
                vertex_counter++;
            }
        }
        vertex_counter = N_vertex;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < i + 1; j++) {
                edges.push_back(make_pair(vertex_counter - i - 1, vertex_counter));
                edges.push_back(make_pair(vertex_counter - i - 2, vertex_counter));
                vertex_counter--;
            }
        }

        sort(edges.begin(), edges.end(), [](const pii& left, const pii& right) {
            return left.second < right.second;
        });
        sort(edges.begin(), edges.end(), [](const pii& left, const pii& right) {
            return left.first < right.first;
        });
    };

    ~GridGraph(){};
};

class ZDDNode {
public:
    unsigned int depth;
    int s;
    int t;
    mii mate;
    vector<ZDDNode*> child;
    int64_t counter;

    ZDDNode()
        : depth(0)
        , mate(mii())
        , s(0)
        , t(0)
        , child(vector<ZDDNode*>())
        , counter(0){};

    ZDDNode(int _depth, const mii& _mate, int _s, int _t)
        : depth(_depth)
        , mate(_mate)
        , s(_s)
        , t(_t)
        , child(vector<ZDDNode*>(2))
        , counter(0)
    {
    }

    ~ZDDNode(){};

    int get_degree(int p)
    {
        if (mate.count(p) == 0 || mate[p] == p) {
            return 0;
        } else if (mate[p] == 0) {
            return 2;
        } else {
            return 1;
        }
    }

    int is_path(pii& edge, int x)
    {
        if (x == 0) {
            return 2;
        }
        int p = edge.first;
        int q = edge.second;
        int p_deg = get_degree(p);
        int q_deg = get_degree(q);

        if (p_deg == 2 || q_deg == 2) {
            return 0;
        }
        if ((p == s || p == t) && p_deg == 1) {
            return 0;
        }
        if ((q == s || q == t) && q_deg == 1) {
            return 0;
        }

        int mate_p;
        int mate_q;

        if (mate.count(q) == 0) {
            mate_q = q;
        } else {
            mate_q = mate[q];
        }

        if (mate.count(p) == 0) {
            mate_p = p;
        } else {
            mate_p = mate[p];
        }

        if (mate_p == q && mate_q == p) {
            return 0;
        }

        if ((mate_p == s && mate_q == t) || (mate_p == t && mate_q == s)) {
            for (auto v : mate) {
                if (get_degree(v.first) == 1) {
                    if (v.first != s && v.first != t && v.first != p && v.first != q) {
                        return 0;
                    }
                }
            }
            return 1;
        } else {
            return 2;
        }
    }

    void update_mate(pii& edge)
    {
        int p = edge.first;
        int q = edge.second;
        if (mate.count(p) == 0) {
            mate[p] = p;
        }
        if (mate.count(q) == 0) {
            mate[q] = q;
        }

        int end_p = mate[p];
        int end_q = mate[q];

        if (get_degree(p) == 1) {
            mate[p] = 0;
            mate[end_p] = end_q;
        } else {
            mate[p] = end_q;
        }

        if (get_degree(q) == 1) {
            mate[q] = 0;
            mate[end_q] = end_p;
        } else {
            mate[q] = end_p;
        }
    }

    vector<int> to_key()
    {
        vector<int> key(ARRAY_SIZE * 2, 0);
        int idx = 0;
        for (auto m : mate) {
            key[idx++] = m.first;
        }
        idx = ARRAY_SIZE;
        for (auto m : mate) {
            key[idx++] = m.second;
        }
        return key;
    }

    bool del_from_mate(const vector<pii>& edges, int p)
    {
        bool is_path = true;
        if (edges.size() > depth) {
            if (edges[depth].first != p && mate.count(p) != 0) {
                if (p == s || p == t) {
                    if (get_degree(p) == 0) {
                        is_path = false;
                    }
                } else {
                    if (get_degree(p) == 1) {
                        is_path = false;
                    }
                }
                mate.erase(p);
            }
        }
        return is_path;
    }
};

class ZDD {
public:
    GridGraph grid_graph;
    vector<pii> edges;
    size_t max_depth;
    int s;
    int t;
    ZDDNode* root;
    ZDDNode* zero;
    ZDDNode* one;
    vector<vector<ZDDNode*>> nodes;
    const mii map_def = mii{
        { 1, 1 },
    };
    const mii map_none = mii();

    ZDD()
        : grid_graph(GridGraph())
        , edges(0)
        , max_depth(0)
        , s(0)
        , t(0)
    {
    }

    ZDD(GridGraph& _grid_graph)
        : grid_graph(_grid_graph)
        , edges(grid_graph.edges)
        , max_depth(edges.size())
        , s(1)
        , t(edges[max_depth - 1].second)
    {
        root = new ZDDNode(0, map_def, s, t);
        root->counter = 1;
        zero = new ZDDNode(-1, map_none, s, t);
        one = new ZDDNode(-2, map_none, s, t);
        nodes = vector<vector<ZDDNode*>>(max_depth + 1, vector<ZDDNode*>());
        nodes[0].push_back(root);
    }

    ~ZDD(){};

    int64_t count_st_path()
    {
        for (unsigned int depth = 0; depth < edges.size(); depth++) {
            printf("\r depth: %d/%zu", depth + 1, max_depth);
            pii e = edges[depth];
            unordered_map<vector<int>, ZDDNode*> mate_dict;
            int p = e.first;
            for (ZDDNode* node : nodes[depth]) {
                for (int x = 0; x <= 1; x++) {
                    int type_child = node->is_path(e, x);
                    if (type_child == 0) {
                        node->child[x] = zero;
                    } else if (type_child == 1) {
                        node->child[x] = one;
                    } else {
                        ZDDNode* ch = new ZDDNode(depth + 1, node->mate, s, t);
                        if (x == 1) {
                            ch->update_mate(e);
                        }
                        if (!ch->del_from_mate(edges, p)) {
                            node->child[x] = zero;
                        } else {
                            vector<int> key = ch->to_key();
                            if (mate_dict.count(key) != 0) {
                                node->child[x] = mate_dict[key];
                            } else {
                                node->child[x] = ch;
                                mate_dict[key] = ch;
                                nodes[depth + 1].push_back(node->child[x]);
                            }
                        }
                    }
                    node->child[x]->counter += node->counter;
                }
            }
            mate_dict.clear();
            nodes[depth].clear();
            nodes[depth].shrink_to_fit();
        }
        cout << "\nNumber of s-t path:" << one->counter << "\n";
        return one->counter;
    }
};

int main(int argc, char const* argv[])
{
    if (argc != 2) {
        return -1;
    }
    int n = atoi(argv[1]);
    GridGraph grid_graph = GridGraph(n);
    printf("Grid:%d\n", n);
    printf("Number of Edges:%d\n", grid_graph.edges.size());

    ZDD zdd = ZDD(grid_graph);
    auto start = chrono::system_clock::now();
    zdd.count_st_path();
    auto end = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "time:" << duration / 1000.0 << "s\n";

    return 0;
}