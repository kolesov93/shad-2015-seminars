#include <iostream>
#include <set>
#include <string>
#include <map>
#include <vector>
using namespace std;
string s;set<string> w;map<string, unsigned char> a,b;vector<string> t;
int main(){
	while(cin>>s){w.insert(s);t.push_back(s);}cout<<w.size()<<" ";
	int k = 0;for(string s:w){
		a[s]=((unsigned char)(50+k/100));b[s]=((unsigned char)(50+k%100));
		cout<<s<< " ";++k;}
	for(string s:t){cout<<a[s]<<b[s];}return 0;}