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
char s[2000000];
int num,alfa[555];
string ss,d[11111];

map<pair<unsigned char, unsigned char>, int> a;
map<pair<unsigned char, unsigned char>, unsigned char> code;



vector<pair<int, pair<unsigned char,unsigned char> > > v;


int main() {
	freopen("input.txt","r",stdin);
	freopen("compressed.txt","w",stdout);
	gets(s);
	int n = strlen(s);
	alfa[s[0]] = 1;
	alfa[24] = 1;
	alfa[25] = 1;
	alfa[26] = 1;
	                
	for (int i = 1; i < n; ++i) {
		a[make_pair(s[i - 1], s[i])]++;
		alfa[s[i]] = 1;
		
	} 
	int kol = 0;
	for (int i = 0; i < 256; ++i) if (alfa[i] == 0) ++kol;
	for (auto it = a.begin(); it != a.end(); ++it) {
		v.push_back(make_pair(it->S, it->F));
	}
	sort(v.begin(), v.end());
	reverse(v.begin(), v.end());
	int last_free = 0;
	cout << kol;
	for (int i = 0; i < v.size(); ++i) {
		while (alfa[last_free] == 1) {
			last_free++;
		}
		if (last_free == 256) {
			break;
		}
		++kol;
		code[make_pair(v[i].S.F,v[i].S.S)] = last_free;
	        cout<<(char)last_free << v[i].S.F << v[i].S.S;
		last_free++;
	
	}
	for (int i = 0; i < n - 1; ++i) {
		if (code.find(make_pair(s[i], s[i + 1])) != code.end()) {
			cout << code[make_pair(s[i], s[i + 1])];
			++i;
		} else {
			cout << s[i];
			if (i == n - 2) cout << s[n - 1];
		}
	}
	putchar(char(25));

	 
        return 0;
}