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
    for (int i = 0; i < n; ++i) {
        int result = 0;
        for (int j = 0; j < i; ++j) {
            int candidate = 0;
            while (i + candidate < n && s[i + candidate] == s[j + candidate]) ++candidate;
            result = max(result, candidate);
        }
        cout << result << " ";
    }
    cout << endl;

    return 0;
}

