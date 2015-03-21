#include <iostream>
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

int main() {
    string s;
    cin >> s;

    auto res1 = calculate_z_function_v1(s);
    auto res2 = calculate_prefix_function(s);
    int sum1 = 0, sum2 = 0;
    for (const auto x : res1) {
        cout << x << " ";
        sum1 += x;
    }
    cout << endl;
    for (const auto x : res2) {
        cout << x << " ";
        sum2 += x;
    }
    cout << endl;
    cout << "z: " << sum1 << " prefix: " << sum2 << endl;

    return 0;
}

