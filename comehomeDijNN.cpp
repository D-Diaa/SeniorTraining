/*
TASK: comehome
LANG: C++14
*/

#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int N  = 200 + 5, M = 4e6 + 5;

int mat[N][N], dist[N], notVis[N], n;

void DIJ(int src)
{
    iota(notVis, notVis + n, 0);
    memset(dist, 0x3f, n * (sizeof dist[0]));
    int nxt = src, sz = n, best;
    dist[src] = 0;
    while(~nxt)
    {
        int u = notVis[nxt];
        notVis[nxt] = notVis[--sz];
        nxt = -1;
        best = 0x3f3f3f3f;
        for(int i = 0 ; i < sz ; i++)
        {
            int v = notVis[i];
            int d = dist[u] + mat[u][v];
            if(dist[v] > d) dist[v] = d;
            if(best > dist[v]) best = dist[v], nxt = i;
        }
    }
}

int main()
{
    freopen("comehome.in", "r", stdin);
    freopen("comehome.out", "w", stdout);
    memset(mat, 0x3f, sizeof mat);
    int m, c;
    char u, v;
    n = 128;
    scanf("%d", &m);
    while(m--)
    {
        scanf(" %c %c%d", &u, &v, &c);
        mat[u][v] = mat[v][u] = min(mat[v][u], c);
    }
    DIJ('Z');
    char res = min_element(dist + 'A', dist + 'Z') - dist;
    printf("%c %d\n", res, dist[res]);
    return 0;
}
