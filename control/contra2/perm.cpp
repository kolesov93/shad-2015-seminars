#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> a = {1,0,2,1,0};
    next_permutation(begin(a), end(a));
    for (int x : a) cout << x << " ";
    cout << endl;

    return 0;
}
