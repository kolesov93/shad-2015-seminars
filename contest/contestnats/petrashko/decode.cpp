#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
using namespace std;
string s;vector<string> c;
int main(){
	int n;cin>>n;getchar();
	for(int i=0;i<n;++i){cin>>s;c.push_back(s);}getchar();getline(cin,s);
	for(int i=0;i<s.length();i+=2){cout<<c[((s[i]+256)%256-50)*100+((s[i+1]+256)%256-50)]<<" ";}
	cout<<"\n";return 0;}
