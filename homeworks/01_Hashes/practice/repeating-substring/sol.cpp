#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;
const int MOD = 1000000007;
const int P = 37;
const int N = 101111;
char s[N];
int pows[N], cumhash[N];
int sufarray[N];
int n;

int substr_cumhash(int l, int r) {
    int result = cumhash[r];
    if (l) result = (result + MOD - cumhash[l - 1]) % MOD;
    return (((long long) result) * pows[n - l]) % MOD;
}

bool random_check(int a, int b, int len) {
    for (int i = 0; i < 5; ++i) {
        int pos = rand() % len;
        if (s[a + pos] != s[b + pos]) {
            return false;
        }
    }
    return true;
}

int main() {
    gets(s);
    n = strlen(s);

    pows[0] = 1;
    for (int i = 0; i < n; ++i) {
        cumhash[i] = (cumhash[i - 1] + ((long long) pows[i]) * (s[i] - 'a' + 1)) % MOD;
        pows[i + 1] = (((long long) pows[i]) * P) % MOD;
        sufarray[i] = i;
    }
    cumhash[n] = cumhash[n - 1]; 

    int l = 0, r = n;
    while (l < r) {
        int center = (l + r + 1) >> 1;

        vector<pair<int, int> > fingerprints;
        fingerprints.reserve(n - center + 1);
        for (int i = 0; i + center <= n; ++i) {
            fingerprints.push_back(make_pair(substr_cumhash(i, i + center - 1), i)); 
        }
        sort(fingerprints.begin(), fingerprints.end());

        bool found = false;
        for (int i = 0; i + 1 < fingerprints.size(); ++i)
            if (fingerprints[i].first == fingerprints[i + 1].first && random_check(fingerprints[i].second, fingerprints[i + 1].second, center)) {
                found = true;
                break;
            }
        if (!found) {
            r = center - 1;
        } else {
            l = center;
        }
    }

    cout << l << endl;

    return 0;
}

