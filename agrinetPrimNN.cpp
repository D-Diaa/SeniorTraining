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

const int N = 1e2 + 5;

int mat[N][N], notVis[N], dist[N], n;

int Prim(int src)
{
    int ret = 0;
    iota(notVis, notVis + n, 0);
    memset(dist, 0x3f, n * (sizeof dist[0]));
    int nxt = src, sz = n, best = 0;
    dist[src] = 0;
    while(~nxt)
    {
        ret += best;
        int u = notVis[nxt];
        notVis[nxt] = notVis[--sz];
        nxt = -1;
        best = 0x3f3f3f3f;
        for(int i = 0 ; i < sz ; i++)
        {
            int v = notVis[i];
            int d = mat[u][v];
            if(dist[v] > d) dist[v] = d;
            if(best > dist[v]) best = dist[v], nxt = i;
        }
    }
    return ret;
}

int main()
{
    freopen("agrinet.in", "r", stdin);
    freopen("agrinet.out", "w", stdout);
    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            scanf("%d", mat[i] + j);
        }
    }
    printf("%d\n", Prim(0));
    return 0;
}
