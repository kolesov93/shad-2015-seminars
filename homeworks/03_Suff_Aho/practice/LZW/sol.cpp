#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class sufarray {
public:
    sufarray(const string& ss)
        : s(ss)
    {
        build();
        kasai();
    }


    void debug_print() {
        for (size_t i = 0; i < array.size(); ++i) {
            cout << s.substr(array[i]);
            if (i + 1 < array.size()) cout << " " << lcp[i];
            cout << endl;
        }
    }
private:
    void kasai() {
        int n = s.size();
        lcp.resize(n - 1);

        vector<int> where(n);
        for (int i = 0; i < n; ++i) {
            where[ array[i] ] = i;
        }


        int secure = 0;
        for (int i = 0; i < n; ++i) {
            int pos1 = i;
            if (where[i] == n - 1) {
                secure = 0;
                continue;
            }
            int pos2 = array[where[i] + 1];
            int maxpos = max(pos1, pos2);
            lcp[where[i]] = secure;
            while (maxpos + lcp[where[i]] < n && s[pos1 + lcp[where[i]]] == s[pos2 + lcp[where[i]]]) ++lcp[where[i]];
            secure = max(0, lcp[where[i]] - 1);
        }
    }

    void build() {
        s.push_back('a' - 1);
        int n = s.size();
        array.resize(n);
        vector<int> classes_count(max(n, 27));
        vector<int> suffix_class(n);
        for (int i = 0; i < n; ++i) {
            suffix_class[i] = s[i] - 'a' + 1;
            classes_count[suffix_class[i]]++;
        }
        for (size_t i = 1; i < classes_count.size(); ++i) {
            classes_count[i] += classes_count[i - 1];
        }
        for (int i = 0; i < n; ++i) {
            array[--classes_count[s[i] - 'a' + 1]] = i;
        }

        for (int level = 0; (1 << level) < n; ++level) {
            int shift = (1 << level);
            fill(classes_count.begin(), classes_count.end(), 0);
            for (int i = 0; i < n; ++i) {
                classes_count[suffix_class[i]]++;
            }
            for (size_t i = 1; i < classes_count.size(); ++i) {
                classes_count[i] += classes_count[i - 1];
            }

            vector<int> new_array(n);
            for (int i = n - 1; i >= 0; --i) {
                int position = (n + array[i] - shift) % n;
                new_array[--classes_count[suffix_class[position]]] = position;
            }
            array = new_array;

            vector<int> new_suffix_class(n);
            new_suffix_class[array[0]] = 0;
            int prev1 = suffix_class[array[0]], prev2 = suffix_class[(array[0] + (1 << level)) % n];
            for (int i = 1; i < n; ++i) {
                int cur1 = suffix_class[array[i]], cur2 = suffix_class[(array[i] + (1 << level)) % n];
                new_suffix_class[array[i]] = new_suffix_class[array[i - 1]];
                if (prev1 != cur1 || prev2 != cur2) {
                    new_suffix_class[array[i]]++;
                }
                prev1 = cur1;
                prev2 = cur2;
            }
            suffix_class = new_suffix_class;
        }

        s = s.substr(0, int(s.size()) - 1);
        array.erase(array.begin());
    }
public:
    vector<int> array;
    vector<int> lcp;

private:
    string s;
};

const int N = 500555;
struct cell {
    int l, r, mn;
} a[4*N];

void build(int x, int l, int r, const sufarray& sr) {
    a[x].l = l; a[x].r = r;
    if (l < r) {
        build(x + x, l, (l + r) >> 1, sr);
        build(x + x + 1, ((l + r) >> 1) + 1, r, sr);
        a[x].mn = min(a[x + x].mn, a[x + x + 1].mn);
    } else {
        a[x].mn = sr.lcp[a[x].l];
    }
}

int findmin(int x, int l, int r) {
    if (r < a[x].l || l > a[x].r) return 1e9;
    if (l <= a[x].l && a[x].r <= r) return a[x].mn;
    return min(findmin(x + x, l, r), findmin(x + x + 1, l, r));
}

int main() {
    string s;
    cin >> s;
    if (s.size() == 1) {
        cout << 0 << endl;
        return 0;
    }
    if (s.size() == 0) {
        return 0;
    }

    sufarray sr(s);
    int n = s.size();
    vector<int> ans(n);
    build(1, 0, n - 2, sr);

    vector<int> stack;
    for (int i = 0; i < n; ++i) {
        int cur = sr.array[i];
        while (stack.size() > 0 && sr.array[stack.back()] > cur) stack.pop_back();
        if (stack.size() > 0) {
            ans[cur] = max(ans[cur], findmin(1, stack.back(), i - 1));
        }
        stack.push_back(i);
    }
    stack.clear();
    for (int i = n - 1; i >= 0; --i) {
        int cur = sr.array[i];
        while (stack.size() > 0 && sr.array[stack.back()] > cur) stack.pop_back();
        if (stack.size() > 0) {
            ans[cur] = max(ans[cur], findmin(1, i, stack.back() - 1));
        }
        stack.push_back(i);
    }

    for (int i = 0; i < n; ++i) cout << ans[i] << " ";
    cout << endl;

    return 0;
}

