#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;
int n,a[256],x,C=2;
string s,tmp,cpy;
vector<pair<int, string> > v;
map<string, int> m;
vector<pair<char, string> > p;
#define se second
#define fi first
#define be begin()
void build(int x)
{
	m.clear();v.clear();
	string S="";
	int i=0;
	while(i<x) S+=s[i++];
	m[S]++;
	for(i=x;i<s.size();++i)
	{
		S.erase(S.be);
		S.insert(S.be+(x-1), s[i]);
		m[S]++;
	}
	for(map<string, int>::iterator it=m.be;it!=m.end();it++)
		v.push_back(make_pair(it->se, it->fi));
	sort(v.rbegin(), v.rend());
}
int main()
{
	ifstream cin("input.txt");
	ofstream cout("compressed.txt");
	getline(cin,s); n=s.size();
	for(int i=0; i<n; ++i) ++a[s[i]];
	build(C);
	for(int i=32;i<255;++i)
	{
		if (i==127||a[i]) continue;
		p.push_back(make_pair(char(i), v[0].second));
		for(int j=0;j+C<s.size();++j)
		{
			bool t=true;
			for(int k=0; k<C; ++k)
				if (v[0].se[k]!=s[j+k])
				{
					t=false;
					break;
				}
			if (t)
			{
				s.erase(s.be+j, s.be+j+C);
				s.insert(s.be+j, char(i));
			}
		}
		v.erase(v.be);
	}
	cout<<p.size()<<endl;
	for(int i=0;i<p.size();++i)
		cout<<p[i].fi<<" "<<p[i].se<<endl;
	cout<<s<<endl;
	return 0;
}