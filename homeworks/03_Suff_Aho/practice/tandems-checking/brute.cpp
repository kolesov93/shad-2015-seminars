#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <cstring>

using namespace std;


int main() {
    string s;
    cin >> s;
    int n = s.size();

    int q;
    cin >> q;
    while (q--) {
        int l, k;
        cin >> l >> k;
        if (l + k + k > n) putchar('0');
        else {
            bool cool = true;
            for (int i = 0; i < k; ++i)
                if (s[l + i] != s[l + k + i]) {
                    cool = false;
                    break;
                }
            if (cool) putchar('1');
            else putchar('0');
        }
    }
    cout << endl;

    return 0;
}

