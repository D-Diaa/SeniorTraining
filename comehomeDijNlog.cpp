/*
TASK: comehome
LANG: C++14
*/

#include <bits/stdc++.h>
#define ll long long
#define S second
#define F first
#define neig(a, u, e, v) for(int v, e = a.head[u] ; ~e and (v = a.to[e], 1) ; e = a.nxt[e])

using namespace std;

const int N  = 200 + 5, M = 2e4 + 5;

int dist[N];

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


void DIJ(int src)
{
    memset(dist, 0x3f, adj.n * (sizeof dist[0]));
    dist[src] = 0;
    priority_queue<pair<int, int> > Q;
    Q.emplace(0, src);
    while(Q.size())
    {
        int d = -Q.top().F;
        int u = Q.top().S;
        Q.pop();
        if(dist[u] != d) continue;
        neig(adj, u, e, v)
        {
            int dd = dist[u] + adj.cost[e];
            if(dist[v] > dd)
            {
                dist[v] = dd;
                Q.emplace(-dd, v);
            }
        }
    }
}

int main()
{
    freopen("comehome.in", "r", stdin);
    freopen("comehome.out", "w", stdout);
    int m, c;
    char u, v;
    adj.init(128);
    scanf("%d", &m);
    while(m--)
    {
        scanf(" %c %c%d", &u, &v, &c);
        adj.addBiEdge(u, v, c);
    }
    DIJ('Z');
    char res = min_element(dist + 'A', dist + 'Z') - dist;
    printf("%c %d\n", res, dist[res]);
    return 0;
}
