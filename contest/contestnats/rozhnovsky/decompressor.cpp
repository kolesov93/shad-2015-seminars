#include <fstream>
#include <string>
#include <map>
using namespace std;
string s;
int n;
char c;
map<char,string>m;
#define b begin()
int main()
{
	ifstream cin("compressed.txt");
	ofstream cout("output.txt");
	cin>>n;
	getline(cin,s);
	for(int i=0;i<n;++i)
	{
		getline(cin,s);
		c=s[0];
		s.erase(s.b,s.b+2);
		m[c]=s;
	}
	getline(cin, s);
	for(int i=0;i<s.size();++i)
		if (m.find(s[i])!=m.end())
		{
			s.insert(s.b+(i+1),m[s[i]][1]);
			s.insert(s.b+(i+1),m[s[i]][0]);
			s.erase(s.b+i);
		}
	cout<<s<<endl;
	return 0;
}