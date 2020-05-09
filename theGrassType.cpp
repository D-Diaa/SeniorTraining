//https://www.hackerearth.com/practice/algorithms/graphs/depth-first-search/practice-problems/algorithm/the-grass-type/

#include<bits/stdc++.h>
#include<ext/numeric>
#define S second
#define F first
#define ll long long
#define neig(a, u, e, v) for(int v, e = (a).head[u] ; e and (v = (a).to[e], 1) ; e = (a).nxt[e])

using namespace std;

const int N = 1e5 + 5, M = N * 2, NM1 = N - 1;

struct Data
{
    unordered_map<int, int> freq;
    int get(int lca, int val)
    {
        return freq[lca / val] * (lca % val == 0);
    }
    void add(int val)
    {
        freq[val]++;
    }
};

struct Adj {
	int head[N], nxt[M], to[M], ne, n;
	void init(int n)
    {
		memset(head + 1, 0, n * sizeof(head[0]));
		ne = 2;
		this->n = n;
	}
	void addEdge(int f, int t)
    {
		nxt[ne] = head[f];
		to[ne] = t;
		head[f] = ne++;
	}
	void addBiEdge(int f, int t)
    {
		addEdge(f, t);
		addEdge(t, f);
	}
	int addNode()
    {
		head[++n] = 0;
		return n;
	}
}adj;

int n, m, par[N], sz[N], dfsOrder[N], sTime[N], eTime[N], value[N], dep[N], curT;

void calcSz(int u)
{
    sz[u] = 1;
    dfsOrder[sTime[u] = curT++] = u;
    neig(adj, u, e, v)
    {
        if(v == par[u]) continue;
        par[v] = u;
        dep[v] = dep[u] + 1;
        calcSz(v);
        sz[u] += sz[v];
    }
    eTime[u] = curT - 1;
}

ll ans;

Data smallToLarge(int u)
{
    Data ret;
    int bg = -1;
    neig(adj, u, e, v)
    {
        if(v == par[u]) continue;
        if(sz[v] * 2 > sz[u]) bg = v;
        else smallToLarge(v);
    }
    if(~bg) ret = smallToLarge(bg);
    ans += ret.get(value[u], value[u]);
    ret.add(value[u]);
    neig(adj, u, e, v)
    {
        if(v == par[u]) continue;
        if(sz[v] * 2 > sz[u]) continue;
        for(int i = sTime[v] ; i <= eTime[v] ; i++)
        {
            int w = dfsOrder[i];
            ans += ret.get(value[u], value[w]);
        }
        for(int i = sTime[v] ; i <= eTime[v] ; i++)
        {
            int w = dfsOrder[i];
            ret.add(value[w]);
        }
    }
    return ret;
}

int main()
{
    // freopen("in.txt", "r", stdin);
    int p, u, v;
    scanf("%d", &n);
    adj.init(n);
    for(int i = 2 ; i <= n ; i++)
    {
        scanf("%d%d", &u, &v);
        adj.addBiEdge(u, v);
    }
    for(int i = 1 ; i <= n ; i++) scanf("%d", value + i);
    calcSz(1);
    smallToLarge(1);
    printf("%lld\n", ans);
    return 0;
}
