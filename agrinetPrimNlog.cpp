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

int mat[N][N], vis[N], vid, dist[N];

struct Adj {
	int head[N], nxt[M], to[M], cost[M], ne, n;
	void init(int n) {
		memset(head, -1, n * sizeof(head[0]));
		ne = 0;
		this->n = n;
	}
	void addEdge(int f, int t, int c) {
		nxt[ne] = head[f];
		to[ne] = t;
        cost[ne] = c;
		head[f] = ne++;
	}
	void addBiEdge(int f, int t, int c) {
		addEdge(f, t, c);
		addEdge(t, f, c);
	}
	int addNode() {
		head[++n] = 0;
		return n;
	}
} adj;

int Prim(int src)
{
    int ret = 0;
    vid++;
    memset(dist, 0x3f, adj.n * (sizeof dist[0]));
    dist[src] = 0;
    priority_queue<pair<int, int> > Q;
    Q.emplace(0, src);
    while(Q.size())
    {
        int d = -Q.top().F;
        int u = Q.top().S;
        Q.pop();
        if(vis[u] == vid) continue;
        ret += d;
        vis[u] = vid;
        neig(adj, u, e, v)
        {
            if(vis[v] == vid) continue;
            int dd = adj.cost[e];
            if(dist[v] > dd)
            {
                dist[v] = dd;
                Q.emplace(-dd, v);
            }
        }
    }
    return ret;
}

int main()
{
    freopen("agrinet.in", "r", stdin);
    freopen("agrinet.out", "w", stdout);
    scanf("%d", &adj.n);
    adj.init(adj.n);
    int c;
    for(int i = 0 ; i < adj.n ; i++)
    {
        for(int j = 0 ; j < adj.n ; j++)
        {
            scanf("%d", &c);
            adj.addEdge(i, j, c);
        }
    }
    printf("%d\n", Prim(0));
    return 0;
}
