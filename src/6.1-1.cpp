/* conference http://www-igm.univ-mlv.fr/~lecroq/string/node18.html */

#include <cstring>
#include <iostream>
#include <string>

#define ASIZE 128 /* ASCII文字の総数 */

using namespace std;

void init_matchtable(int table[], string str)
{
    int len = str.length();
    for (int i = 0; i < ASIZE; i++) {
        table[i] = len;
    }
    for (int i = 0; i < len - 1; i++) {
        table[(int)str[i]] = len - i - 1;
    }
}

int main()
{
    string text;
    string pattern;

    /* スペースが含まれた文章からの検索も有効にするため，cinではなくgetlineを用いた */
    cout << "text? : ";
    getline(cin, text);
    cout << "pattern? : ";
    getline(cin, pattern);

    int plen = pattern.length();
    int tlen = text.length();
    int match_table[ASIZE];
    int match_positions[tlen];

    /* 文字ごとの移動量を決定 */
    init_matchtable(match_table, pattern);

    /* 移動量のテーブルを表示 */
    bool shown[ASIZE];
    cout << "\n[match table]\n";
    for (int i = 0; i < plen; i++) {
        if (!shown[(int)pattern[i]]) {
            shown[(int)pattern[i]] = true;
            cout << pattern[i] << " " << match_table[(int)pattern[i]] << "\n";
        }
    }
    cout << "others " << plen << "\n";

    /* 検索 */
    cout << "\n[process]\n";
    int found_count = 0;
    int pos = 0;
    while (pos <= tlen - plen) {
        /* patternの末尾と比較していく */
        char c = text[pos + plen - 1]; /* patternの末尾に対応するtext */
        bool matches = (pattern[plen - 1] == c && memcmp(pattern.c_str(), text.c_str() + pos, plen - 1) == 0);
        if (matches) {
            match_positions[found_count++] = pos;
        }

        /* 過程の表示 */
        cout << text << "\n";
        cout << string(pos, ' ') << pattern;
        cout << string(tlen - pos - plen + 1, ' ') << "shift " << match_table[c] << "(table[" << c << "])";
        cout << (matches ? " <- matches!\n" : "\n");

        pos += match_table[c];
    }

    /* 検索結果表示 */
    cout << "\n[result]\n";
    cout << found_count << " found\n";
    cout << text << "\n";
    for (int i = 0, j = 0, k = 0; i < tlen; i++) {
        if (i == match_positions[k]) {
            j = plen;
            k++;
        }
        cout << (j-- > 0 ? "^" : " ");
    }
}