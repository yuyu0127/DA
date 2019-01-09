#include <iostream>
#include <vector>

#define MAX_COUNT 65536

using namespace std;

/**
 * @brief 安定マッチングのペアを得る
 * 
 * @param order_m 各男性の，女性のIDを希望順に並べたもの
 * @param order_w 各女性の，男性のIDを希望順に並べたもの
 * @return vector<int> 各男性の，マッチング相手のID
 */
vector<int> stable_matching(const vector<vector<int>>& order_m, const vector<vector<int>>& order_w)
{
    const int N = order_m.size(); /* 女性(男性)の人数 */
    vector<vector<int>> priority_w(N, vector<int>(N + 1, N)); /* priority_w[w][m]は、女性wの男性mに対する優先度(ただし、存在しない相手の優先度は最低) */
    vector<int> current_partner_m(N, N); /* current_partner_m[m]は、男性mのマッチング相手(Nで初期化) */
    vector<int> proposed_m(N, 0); /* proposed_m[m]は、男性mが何番目の女性までプロポースしたか */

    cout << "\n[men's order(alphabet)]\n";
    for (int i = 0; i < order_m.size(); i++) {
        auto raw = order_m[i];
        cout << char(i + 65) << ": ";
        for (auto elem : raw) {
            cout << char(elem + 65 + 32) << " ";
        }
        cout << "\n";
    }
    cout << "[women's order(alphabet)]\n";
    for (int i = 0; i < order_w.size(); i++) {
        auto raw = order_w[i];
        cout << char(i + 65 + 32) << ": ";
        for (auto elem : raw) {
            cout << char(elem + 65) << " ";
        }
        cout << "\n";
    }

    /* 希望順をもとに優先度を設定する */
    for (int w = 0; w < N; w++) {
        for (int i = 0; i < N; i++) {
            priority_w[w][order_w[w][i]] = i;
        }
    }

    /* 表示用 */
    cout << "[women's priority on men]\n   ";
    for (int i = 0; i < N; i++) {
        cout << char(i + 65) << " ";
    }
    cout << "_\n";
    for (int i = 0; i < priority_w.size(); i++) {
        auto raw = priority_w[i];
        cout << char(i + 65 + 32) << ": ";
        for (auto elem : raw) {
            cout << elem << " ";
        }
        cout << "\n";
    }

    /* メインの処理 */
    for (int i = 0; i < N; i++) {
        for (int m = i; m < N;) {
            /* wはmがまだプロポーズしていない中で一番好みの女性 */
            int w = order_m[m][proposed_m[m]++];
            if (priority_w[w][m] < priority_w[w][current_partner_m[w]]) {
                /* wにとって、今のパートナーよりも新たなパートナーmの方が良ければ交換 */
                /* つまり、mとcurrent_partner_m[w]でmの方が優先度が高い場合に交換 */
                /* current_partner_mの初期値は存在しない相手であり、存在しない相手の優先度は */
                /* 最低に設定されているため、最初の処理では必ず交換されるようになっている */
                swap(m, current_partner_m[w]);
            }
        }
    }
    return current_partner_m;
}

int main(int argc, char const* argv[])
{
    int count = 0;

    cout << "number of men(or women) : ";
    cin >> count;

    vector<vector<int>> order_m(count, vector<int>(count));
    vector<vector<int>> order_w(count, vector<int>(count));

    /* 相手を希望順に入力 */
    cout << "men's order\n";
    for (int i = 0; i < count; i++) {
        cout << i << " : ";
        for (int j = 0; j < count; j++) {
            int order;
            cin >> order;
            order_m[i][j] = order;
        }
    }
    cout << "women's order\n";
    for (int i = 0; i < count; i++) {
        cout << i << " : ";
        for (int j = 0; j < count; j++) {
            int order;
            cin >> order;
            order_w[i][j] = order;
        }
    }

    vector<int> matching = stable_matching(order_m, order_w);

    cout << "\n[result]\nM - F\n";
    for (int i = 0; i < count; i++) {
        cout << i << " - " << matching[i] << "\n";
    }

    return 0;
}
