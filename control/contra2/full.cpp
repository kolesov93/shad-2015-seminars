#include <iostream>
#include <algorithm>
using namespace std;

int first_bigger(int* a, int n, int value) {
    if (a[n - 1] < value) return -1;
    int l = 0, r = n - 1;
    while (l < r) {
        int center = (l + r + 1) / 2;
        if (a[center] <= value) l = center + 1;
        else r = center;
    }
    return l;
}

int brute(int* a, int n, int value) {
    for (int i = 0; i < n; ++i)
        if (a[i] > value) return i;
    return -1;
}

int a[111];
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a, a + n);


    cout << first_bigger(a, n, 10) << " " << brute(a, n, 10) << endl;

    return 0;
}
