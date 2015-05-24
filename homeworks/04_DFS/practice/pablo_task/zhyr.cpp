#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>
#include <assert.h>


using namespace std;
int n;
int a[2000][2000];

int lef[2000];
int righ[2000];
int to[2000];
int bot[2000];
vector <int> g[111111];
bool used[2000];
int maxInt = 1000000000;

int l; int r, t, b;

stack<int> st;
vector <int> ans;

void addEdge(int v, int to)
{
    g[v].push_back(to);
}

void dfs (int v) {
    assert(v > 0);
    used[v] = true;
    for (size_t i=0; i<g[v].size(); ++i) {
        int to = g[v][i];
        if (!used[to])
            dfs (to);
    }
    ans.push_back (v);
}

void topological_sort() {
    for (int i=0; i<n; ++i)
        used[i] = false;
    ans.clear();
    for (int i=1; i<=n; ++i)
        if (!used[i] && lef[i] != -1)
        {
            dfs (i);
            l = lef[i];
            r= righ[i];
            t = to[i];
            b= bot[i];
        }
    for (int i=1; i<=n; ++i)
        if (!used[i])
            dfs (i);
    reverse (ans.begin(), ans.end());
}



int main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    cin >> n;
    for (int i =0; i< n; i++)
        for (int j =0; j< n; j++)
        {
            cin >> a[i][j];
        }
    for (int i = 0; i<= n; i++)
        lef[i] = righ[i] = to[i] = bot[i] = -1;




    for (int i = 0; i< n; i++)
        for (int j =0; j< n; j++)
        {
            if (lef[a[i][j]] == -1) lef[a[i][j]] = j;
            if (righ[a[i][j]] == -1) righ[a[i][j]] = j;
            if (to[a[i][j]] == -1) to[a[i][j]] = i;
            if (bot[a[i][j]] == -1) bot[a[i][j]] = i;

            if (lef[a[i][j]] > j) lef[a[i][j]] = j;
            if (righ[a[i][j]] < j) righ[a[i][j]] = j;
            if (to[a[i][j]] > i) to[a[i][j]] = i;
            if (bot[a[i][j]] < i) bot[a[i][j]] = i;
        }

    for (int i =0; i<n; i++)
    {
        while(!st.empty()) st.pop();
        if (a[i][0] != 0) st.push(a[i][0]);
        for (int j = 0; j< n; j++)
            if (a[i][j] != 0)
        {
            if (st.empty()) {st.push(a[i][j]); continue;}
            int curColor = st.top();
            if (curColor == a[i][j])
            {
                continue;
            }
            while (!st.empty() && righ[st.top()] < j)
                st.pop();
            if (!st.empty())
            {
                addEdge(st.top(), a[i][j]);
            }
            st.push(a[i][j]);
        }
    }

    for (int i = 0; i< n; i++)
    {
        while(!st.empty()) st.pop();
        if (a[i][n-1] != 0) st.push(a[i][n-1]);
        for (int j = n-1; j>=0; j--)
            if (a[i][j] != 0)
        {
            if (st.empty()) {st.push(a[i][j]); continue;}
            int curColor = st.top();
            if (curColor == a[i][j])
            {
                continue;
            }
            while (!st.empty() && lef[st.top()] > j)
                st.pop();
            if (!st.empty())
            {
                addEdge(st.top(), a[i][j]);
            }
            st.push(a[i][j]);
        }
    }

    for (int j =0; j<n; j++)
    {
        while(!st.empty()) st.pop();
        if (a[0][j] != 0) st.push(a[0][j]);
        for (int i = 0; i < n; i++)
            if (a[i][j] != 0)
        {
            if (st.empty()) {st.push(a[i][j]); continue;}
            int curColor = st.top();
            if (curColor == a[i][j])
            {
                continue;
            }
            while (!st.empty() && bot[st.top()] < i)
                st.pop();
            if (!st.empty())
            {
                addEdge(st.top(), a[i][j]);
            }
            st.push(a[i][j]);
        }
    }

    for (int j =0; j<n; j++)
    {
        while(!st.empty()) st.pop();
        if (a[n-1][j] != 0) st.push(a[n-1][j]);
        for (int i = n-1; i >=0 ; i--)
            if (a[i][j] != 0)
        {
            if (st.empty()) {st.push(a[i][j]); continue;}
            int curColor = st.top();
            if (curColor == a[i][j])
            {
                continue;
            }
            while (!st.empty() && to[st.top()] > i)
                st.pop();
            if (!st.empty())
            {
                addEdge(st.top(), a[i][j]);
            }
            st.push(a[i][j]);
        }
    }

    topological_sort();


    for (int i = 0; i< n; i++)
    {
        if (lef[ans[i]] == -1)
        {
            cout << ans[i] << ' ';
            cout << t + 1  << ' ' << l + 1 << ' ' << b+ 1  << ' ' << r+ 1  << endl;
            continue;
        }
        cout << ans[i]  << ' ';
        cout << to[ans[i]]+ 1  << ' ' << lef[ans[i]] + 1 <<' ' <<  bot[ans[i]]+ 1 << ' '<< righ[ans[i]] + 1 << ' ' << endl;
    }


    return 0;
}
