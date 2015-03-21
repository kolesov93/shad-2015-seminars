#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;
const int N = 101111;
char s[N];

int main() {
    gets(s);
    int n = strlen(s);

    int ans = 0;
    for (int l = 0; l < n; ++l)
        for (int r = l + 1; r < n; ++r) {
            for (int i = 0; r + i < n; ++i)
                if (s[l + i] == s[r + i]) {
                    ans = max(ans, i + 1);
                } else {
                    break;
                }
        }
    cout << ans << endl;
    

    return 0;
}
