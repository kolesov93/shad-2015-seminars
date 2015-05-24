#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <stdio.h>
#include <fcntl.h>
using namespace std;
#define Q 128
#define S string
#define U (unsigned char)
#define R size
S decode(S s){
vector<int> cnt(Q,0);
for(int i=0;i<s.R();++i)
++cnt[s[i]];
int sum=0;
for(int i=0;i<Q;++i){
sum=sum+cnt[i];
cnt[i]=sum-cnt[i];}
vector<int> t(s.R());
for (int i=0;i<s.R();++i){
t[cnt[s[i]]]=i;
++cnt[s[i]];}
int j=t[s.find('{')];
S r;
for (int i=0;i+1<s.R();++i){
r+=s[j];
j=t[j];}
return r;}
S demtf(S v){
vector<char> curr(Q);
vector<int> rev(Q);
for (int i=0;i<Q;++i)
curr[i]=rev[i]=i;
S s;
for (int i=0;i<v.R();++i){
int w=rev[v[i]];
s+=w;
for (int j=0;j<Q;++j)
if(curr[rev[j]]<curr[w])
++curr[rev[j]];
curr[w]=0;
for (int j=0;j<Q;++j)
rev[curr[j]]=j;}
return s;}
S derle(S s){
for (int i=0;i<s.R();++i)
--s[i];
int i=0;
S ans;
while (i<s.R()){
if (s[i]!='~')
ans.push_back(s[i]);
else{
int rep=0;
int mem=0;
while (s[i]=='~'){
int curr=(int(U(s[i+1]))<<mem);
rep|=curr;
i+=2;
mem+=8;}
for(int j=0;j<rep;++j)
ans.push_back(s[i]);}
++i;}
return ans;
}
S dehamm(S s){
int data=s.find('|');
S dop=s.substr(0,data);
stringstream ss;
ss<<dop;
int total;
ss>>total;
map<vector<bool>,unsigned char >mn;
int c;
long long b;
for (int i=0;i<256;++i){
ss>>c;
if(c){
ss>>b;
vector<bool>vb;
for (int i=0;i<c;++i)
vb.push_back(b&(1ll<<i));
mn[vb]=U(i);}}
vector<bool>all;
S ans;
for (int i=data+1;i<s.R();++i){
for (int j=0;j<8;++j)
all.push_back(s[i]&(1<<j));}
vector<bool>curr;
for (int i=0;i<total;++i){
curr.push_back(all[i]);
if (mn.find(curr)!=mn.end()){
ans+=char(mn[curr]);
curr=vector<bool>();}}
return ans;}
S read(){
S s;
ostringstream cc;
cc<<cin.rdbuf();
s=cc.str();
return s;}
int main(){
ios_base::sync_with_stdio(0);
S s=read();
cout<<decode(demtf(derle(dehamm(s))));}
