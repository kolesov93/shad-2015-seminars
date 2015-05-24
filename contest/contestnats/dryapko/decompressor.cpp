#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<map>
#include<cstring>
#include<algorithm>
#include<vector>
#define F first
#define S second
using namespace std;
char a, b, c;
map<char, pair<char, char> > decode;
int kol;
int main() {
	freopen("compressed.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin >> kol;
	for (int i = 0; i < kol; ++i) {
		c = getchar();
		a = getchar();
		b = getchar();
		decode[c] = make_pair(a, b);
	}
	while (true) {
		c = getchar();
		if (c == char(25)) break;
		if (decode.find(c) != decode.end()) {
			cout << decode[c].F << decode[c].S;
		} else cout << c;
	}
	cout << endl;
        return 0;
}
