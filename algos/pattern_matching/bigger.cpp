#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

vector<size_t> calculate_prefix_function(const string& s) {
    vector<size_t> prefix(s.size());

    for (size_t i = 1; i < prefix.size(); ++i) {
        int k = prefix[i - 1];
        while (k && s[i] != s[k]) {
            k = prefix[k - 1];
        }
        if (s[i] == s[k]) ++k;
        prefix[i] = k;
    }

    return prefix;
}

vector<size_t> calculate_z_function_v1(const string& s) {
    vector<size_t> z(s.size());

    size_t l = 0, r = 0;
    for (size_t i = 1; i < z.size(); ++i) {
        if (r <= i) {
            l = r = i;
            while (r < s.size() && s[r] == s[r - l]) ++r;
            z[i] = r - l;
        } else {
            if (z[i - l] < r - i) {
                z[i] = z[i - l];
                continue;
            }
            z[i] = r - i;
            while (i + z[i] < s.size() && s[i + z[i]] == s[z[i]]) {
                ++z[i];
            }
            if (i + z[i] > r) {
                l = i;
                r = i + z[i];
            }
        }
    }

    return z;
}

vector<size_t> calculate_z_function_v2(const string& s) {
    vector<size_t> z(s.size());

    size_t l = 0, r = 0;
    for (size_t i = 1; i < z.size(); ++i) {
        if (r <= i) {
            l = r = i;
            while (r < s.size() && s[r] == s[r - l]) ++r;
            z[i] = r - l;
        } else {
            z[i] = min(r - i, z[i - l]);
            while (i + z[i] < s.size() && s[i + z[i]] == s[z[i]]) {
                ++z[i];
            }
            if (i + z[i] > r) {
                l = i;
                r = i + z[i];
            }
        }
    }

    return z;
}

vector<size_t> calculate_z_function_v3(const string& s) {
    vector<size_t> z(s.size());

    size_t l = 0, r = 0;
    for (size_t i = 1; i < z.size(); ++i) {
        if (i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while (i + z[i] < s.size() && s[i + z[i]] == s[z[i]]) {
            ++z[i];
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }

    return z;
}

int n;
void rec(int l, string s, char mx) {
    if (l == n) {
        auto prefix = calculate_prefix_function(s);
        auto z = calculate_z_function_v1(s);
        int sum = 0;
        for (int x : prefix) sum += x;
        for (int x : z) sum -= x;
        if (sum > 0) {
            cout << s << endl;
        }
        return;
    }

    for (char c = 'a'; c <= mx + 1; ++c) {
        rec(l + 1, s + c, max(c, mx));
    }
}

int main() {
    cin >> n;

    rec(0, "", 'a' - 1);
    cout << "Sorry. Nothing found" << endl;

    return 0;
}

