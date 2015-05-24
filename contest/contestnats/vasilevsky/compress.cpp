#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <queue>
#include <stdio.h>
#include <fcntl.h>
using namespace std;
#define S string
#define R size
void firstCalc(vector<int>&perm,vector<int>&cls,S&s){
vector<int>v(128,0);
for(int i=0;i<s.R();++i)
++v[s[i]];
for(int i=1;i<v.R();++i)
v[i]+=v[i-1];
for(int i=0;i<s.R();++i)
perm[--v[s[i]]]=i;
for(int i=1;i<s.R();++i)
cls[perm[i]]=cls[perm[i-1]]+(s[perm[i-1]]!=s[perm[i]]);}
struct triple{
int first;
int second;
int ind;
triple(){};
triple(int first,int second,int ind):first(first),second(second),ind(ind){}};
void linearSort(vector<triple>&a){
vector<int>v(a.R(),0);
for (int i=0;i<a.R();++i)
++v[a[i].second];
for (int i=1;i<v.R();++i)
v[i]+=v[i-1];
vector<triple>nw(a.R());
for(int i=0;i<a.R();++i)
nw[--v[a[i].second]]=a[i];
v=vector<int>(a.R(),0);
for(int i=0;i<a.R();++i)
++v[nw[i].first];
for(int i=1;i<v.R();++i)
v[i]+=v[i-1];
for(int i=nw.R()-1;i>=0;--i)
a[--v[nw[i].first]]=nw[i];}
vector<int>suffixArray(S & s){
vector<int>perm(s.R());
vector<int>cls(s.R(),0);
firstCalc(perm,cls,s);
for(int i=1;i<s.R();i*=2){
vector<triple>sortMe(s.R());
for(int j=0;j<sortMe.R();++j)
sortMe[j]=triple(cls[j],cls[(j+i)%s.R()],j);
linearSort(sortMe);
for(int j=0;j<s.R();++j)
perm[j]=sortMe[j].ind;
vector<int>clsNew=vector<int>(cls.R(),0);
for(int j=1;j<s.R();++j)
clsNew[perm[j]]=clsNew[perm[j-1]]+(cls[perm[j-1]]!=cls[perm[j]]||cls[(perm[j-1]+i)%cls.R()]!=cls[(perm[j]+i)%cls.R()]);
swap(cls,clsNew);}
return perm;}
S encode(S&_s){
S s=_s+"{";
int n=s.R();
vector<int>sA=suffixArray(s);
S r;
for(int i=0;i<n;++i)
r+=s[(sA[i]+n-1)%n];
return r;}
#define SZ 128
S enmtf(S s){
vector<int>curr(SZ);
for(int i=0;i<SZ;++i)
curr[i]=i;
S ans;
for(int i=0;i<s.R();++i){
ans+=char(curr[s[i]]);
for(int j=0;j<SZ;++j)
if (curr[j]<curr[s[i]])
++curr[j];
curr[s[i]]=0;}
return ans;}
S rle(S v){
vector<pair<int, int> >d;
for(int i=0;i<v.R();++i)
if(d.empty()||d.back().first!=v[i])
d.push_back(make_pair(v[i],1));
else
++d.back().second;
S ans;
for(int i=0;i<d.R();++i){
if (d[i].second<16)
for(int j=0;j<d[i].second;++j)
ans+=d[i].first;
else{
while(d[i].second){
char curr=d[i].second&255;
d[i].second>>=8;
ans+="~";
ans+=curr;}
ans+=d[i].first;}}
for(int i=0;i<ans.R();++i)
++ans[i];
return ans;}
struct Node{
Node*left;
Node*right;
char value;};
map<char, vector<bool> > mp;
void dfs(Node*curr,vector<bool> vc){
if(!curr->left&&!curr->right){
mp[curr->value] = vc;
return;}
if(curr->left){
vc.push_back(0);
dfs(curr->left,vc);
vc.pop_back();}
if(curr->right){
vc.push_back(1);
dfs(curr->right,vc);
vc.pop_back();}}
S enhamm(S s){
vector<int>cnt(256,0);
for(int i=0;i<s.R();++i)
++cnt[(unsigned char)(s[i])];
priority_queue<pair<int, Node*> >q;
for(int i=0;i<256;++i)
if(cnt[i]){
Node*c=new Node();
c->left=c->right=0;
c->value=i;
q.push(make_pair(-cnt[i],c));}
while (q.R()>=2){
pair<int, Node*>mn=q.top();
q.pop();
pair<int, Node*>mn2=q.top();
q.pop();
Node*node=new Node();
node->left=mn.second;
node->right=mn2.second;
q.push(make_pair(mn.first+mn2.first,node));}
dfs(q.top().second,vector<bool>());
vector<bool> result;
for(int i=0;i<s.R();++i)
for(int j=0;j<mp[(unsigned char)(s[i])].R();++j)
result.push_back(mp[(unsigned char)(s[i])][j]);
int total=result.R();
while(result.R()&7)
result.push_back(0);
S str;
for(int i=0;i<result.R();i+=8){
char x=0;
for(int j=0;j<8;++j)
x|=(result[i+j]<<j);
str+=x;}
stringstream ss;
bool init=0;
vector<pair<int, long long> >v(256);
for(map<char, vector<bool> >::iterator it=mp.begin();it!=mp.end();++it){
long long sh=0;
for(int i=0;i<it->second.R();++i)
if(it->second[i])
sh|=(1ll<<i);
v[int((unsigned char)(it->first))]=make_pair(int(it->second.R()),sh);}
for(int i=0;i<256;++i){
if(init)
ss<<" ";
init=1;
if(v[i]==make_pair(0,0ll))
ss<<0;
else
ss<<v[i].first<<" "<<v[i].second;}
ss<<"|";
S info=ss.str();
stringstream s2;
s2<<total<<" ";
return s2.str()+info+str;}
S read(){
S s;
ostringstream cc;
cc<<cin.rdbuf();
s=cc.str();
return s;}
int main(){
ios_base::sync_with_stdio(0);
S s;
s=read();
S coded=enhamm(rle(enmtf(encode(s))));
cout<<coded;}
