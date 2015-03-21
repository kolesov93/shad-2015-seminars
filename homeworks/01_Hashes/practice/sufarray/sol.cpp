#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

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

bool cmp(int a, int b) {
    if (a == b) return false;

    // how much to shift to get the difference
    int l = 0, r = n - max(a, b);
    while (l < r) {
        int center = (l + r) >> 1;

        int cumhash_a = substr_cumhash(a, a + center);
        int cumhash_b = substr_cumhash(b, b + center);

        if (cumhash_a != cumhash_b) {
            r = center; 
        } else {
            l = center + 1;
        }
    }

    return s[a + l] < s[b + l];
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
    sort(sufarray, sufarray + n, cmp);

    for (int i = 0; i < n; ++i) printf("%d ", sufarray[i] + 1);
    cout << endl;

    return 0;
}

