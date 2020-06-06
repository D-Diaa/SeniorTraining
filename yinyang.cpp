#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5, M = 2*N;

#define neig(adj, u, e, v) for(int e = adj.head[u], v; ~e and (v = adj.to[e], true); e = adj.nxt[e])
#define arr(t, n, s, e) t _##n[e-s+1], *n= _##n+(-s);
map<int, int> showArray(int * a, int s, int e)
{
    map<int, int> ret;
    for(int i = s; i<=e; i++)
        ret[i]=a[i];
    return ret;
}

struct Adj
{
    int head[N], nxt[M], to[M], col[M];
    int n, ne;
    void init(int nn)
    {
        n = nn;
        ne = 0;
        memset(head, -1, nn*sizeof(head[0]));
    }
    void addEdge(int f, int t, int c)
    {
        nxt[ne] = head[f];
        to[ne] = t;
        col[ne] = c;
        head[f] = ne++;
    }
    void addBiEdge(int u, int v, int c)
    {
        addEdge(u, v, c);
        addEdge(v, u, c);
    }
} adj;

int sz[N];
int del[N], delId;

void calcSz(int u, int par)
{
    sz[u] = 1;
    neig(adj, u, e, v)
    {
        if(v == par || del[v] == delId) continue;
        calcSz(v, u);
        sz[u]+=sz[v];
    }
}

//int _dist[2][2*N+1], *dist[2]={_dist[0]+N, _dist[1]+N};

arr(int, depths, -N, N);
arr(int, dist_sat, -N, N);
arr(int, dist_unsat, -N, N);
int*dist[2] = {dist_unsat, dist_sat};
long long res=0;
void updateDist(int u, int par, int d, int dir)
{
    bool z = depths[d]>0;
    dist[z][d]+=dir;

    depths[d]++;
    neig(adj, u, e, v)
    {
        if(v == par || del[v]==delId) continue;
        updateDist(v, u, d+adj.col[e], dir);
    }
    depths[d]--;
}
void updateAnswer(int u, int par, int d)
{
    // add satisfied paths with remaining distance anyways
    res+=dist[1][-d];
    // cumulative depth existed before on that path
    bool z = depths[d]>0;
    // if cumulative depth existed (or this path is zero), then this is a satisfied path
    // add unsatisfied ones (paths in other subtrees)
    if(z||d==0)
        res+=dist[0][-d];
    // Paths ending at the root with a zero node (indicated by z) in the middle
    res+=(z&&d==0);
    // store cumulative depth for this node
    depths[d]++;
    neig(adj, u, e, v)
    {
        if(v == par || del[v]==delId) continue;
        updateAnswer(v, u, d+adj.col[e]);
    }
    // remove cumulative depth for this node
    depths[d]--;
}

void solveTree(int u, int s)
{
    // Build answer
    neig(adj, u, e, v)
    {
        if (del[v] == delId) continue;
        updateAnswer(v, u, adj.col[e]);
        updateDist(v, u, adj.col[e], 1);
    }

    // clear dist array
    neig(adj, u, e, v)
    {
        if (del[v] == delId) continue;
        updateDist(v, u,adj.col[e] , -1);
    }
}
int cPar[N];
int decompose(int u, int p, int s)
{
    //find centroid of current subtree
    neig(adj, u, e, v)
    {
        if(v==p || del[v] == delId) continue;
        if(2*sz[v]>s) return decompose(v, u, s);
    }
    // u is centroid
    del[u] = delId;
    solveTree(u, s);
    neig(adj, u, e, v)
    {
        if (del[v] == delId) continue;
        calcSz(v, u);
        cPar[decompose(v, u, sz[v])]=u;
    }
    return u;
}

void centroid(int root)
{
    res = 0;
    delId++;
    calcSz(root, -1);
    cPar[decompose(root, -1, sz[root])]=-1;
}

int main()
{
#ifdef clion
    freopen("test.in", "r", stdin);
#else
    freopen("yinyang.in", "r", stdin);
    freopen("yinyang.out", "w", stdout);
#endif
    int n, u, v, c;
    scanf("%d", &n);
    adj.init(n);
    for (int i = 0; i < n - 1; ++i)
    {
        scanf("%d%d%d", &u, &v, &c);
        adj.addBiEdge(--u, --v, 2*c-1);
    }
    centroid(0);
    printf("%lld\n", res);
    return 0;
}

// Problem link: http://www.usaco.org/index.php?page=viewproblem2&cpid=286
