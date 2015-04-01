#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#include <set>

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


int main() {
    string s;
    cin >> s;
    long long n = s.size();

    sufarray sr(s);
    long long all = n * (n + 1) / 2 + 1;
    int mx = 0;
    set<int> q;
    for (int i = 0; i + 1 < n; ++i) {
        all -= sr.lcp[i];
        mx = max(mx, sr.lcp[i]);
        q.insert(sr.lcp[i]);
    }
    cout << all << " " << mx << " " << q.size() << endl;


    return 0;
}

