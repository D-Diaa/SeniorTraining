/*
TASK: agrinet
LANG: C++14
*/

#include <bits/stdc++.h>
#define ll long long
#define S second
#define F first
#define neig(a, u, e, v) for(int v, e = a.head[u] ; ~e and (v = a.to[e], 1) ; e = a.nxt[e])

using namespace std;

const int N = 1e2 + 5, M = N * N;

int from[M], to[M], cost[M], sorted[M], ne, n;

struct dsu
{
    vector<int> parent, sz;
    int cmpCnt, mxSz;
    dsu(int n)
    {
        mxSz = 1;
        parent.resize(n);
        sz.resize(n, 1);
        for(int i = 0 ; i < n ; i++) parent[i] = i;
        cmpCnt = n;
    }
    int operator[](int x)
    {
        if(parent[x] == x)return x;
        return parent[x] = (*this)[parent[x]];
    }
    bool operator()(int x, int y)
    {
        x = (*this)[x];
        y = (*this)[y];
        if(x == y) return 0;
        if(sz[x] > sz[y]) swap(x, y);
        parent[x] = y;
        sz[y] += sz[x];
        mxSz = max(mxSz , sz[y]);
        cmpCnt--;
        return 1;
    }
};

int Kruskal()
{
    int ret = 0;
    dsu d(n);
    sort(sorted, sorted + ne, [](int a, int b)
    {
        return cost[a] < cost[b];
    });
    for(int i = 0 ; i < ne ; i++)
    {
        int id = sorted[i];
        if(d(from[id], to[id])) ret += cost[id];
    }
    return ret;
}

int main()
{
    freopen("agrinet.in", "r", stdin);
    freopen("agrinet.out", "w", stdout);
    int c;
    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            scanf("%d", &c);
            from[ne] = i;
            to[ne] = j;
            cost[ne] = c;
            sorted[ne] = ne++;
        }
    }
    printf("%d\n", Kruskal());
    return 0;
}
