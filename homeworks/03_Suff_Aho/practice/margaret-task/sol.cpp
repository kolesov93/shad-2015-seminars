#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int N = 1000111;
int go[N][26], fail[N], parent[N];
char label[N];
int terminal[N];
int size = 1;

void build() {
    queue<int> q;
    for (int i = 0; i < 26; ++i)
        if (go[1][i] == 0) {
            go[1][i] = 1;
        } else {
            fail[go[1][i]] = 1;
            q.push(go[1][i]);
        }
    fail[1] = 1;


    while (!q.empty()) {
        int x = q.front(); q.pop();
        if (!fail[x]) {
            fail[x] = go[ fail[parent[x]] ][size_t(label[x])];
        }
        if (!terminal[x]) {
            terminal[x] = terminal[fail[x]];
        }

        for (int i = 0; i < 26; ++i)
            if (go[x][i] == 0) {
                go[x][i] = go[fail[x]][i];
            } else {
                q.push(go[x][i]);
            }
    }
}
vector<int> ans;

int main() {
    int n, m;
    cin >> n;
    ans.resize(n);
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        reverse(s.begin(), s.end());
        int cur = 1;
        for (size_t j = 0; j < s.size(); ++j) {
            int ch = s[j] - 'a';
            if (!go[cur][ch]) {
                go[cur][ch] = ++size;
                label[size] = ch;
                parent[size] = cur;
            }
            cur = go[cur][ch];
        }
        terminal[cur] = i + 1;
    }
    build();

    cin >> m;
    for (int i = 0; i < m; ++i) {
        vector<bool> used(n);
        string s; cin >> s;
        reverse(s.begin(), s.end());
        int cur = 1;
        for (size_t j = 0; j < s.size(); ++j) {
            int ch = s[j] - 'a';
            cur = go[cur][ch];
            if (terminal[cur] && !used[terminal[cur] - 1]) {
                ans[terminal[cur] - 1]++;
                used[terminal[cur] - 1] = true;
            }
        }
    }

    for (int i = 0; i < n; ++i) cout << ans[i] << '\n';

    return 0;
}

