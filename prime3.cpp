/*
TASK: prime3
LANG: C++14
 */
//#pragma GCC optimize ("O3")
#include<bits/stdc++.h>
#include<ext/numeric>
#define ll long long
#define S second
#define F first

using namespace std;
using namespace __gnu_cxx;
using ull = unsigned long long;

const int N = 161052, M = 24226;

int ne = 1, head[N], to[M], nxt[M], deg[N];

void addEdge(int f, int t)
{
    nxt[ne] = head[f];
    deg[f]++;
    to[ne] = t;
    head[f] = ne++;
}

int sumDig(int x)
{
    int ret = 0;
    while(x)
    {
        ret += x%10;
        x /= 10;
    }
    return ret;
}

bool isPrime(int x)
{
    if(x == 1) return 0;
    for(int i = 2 ; i <= x / i ; i++)
    {
        if(x % i == 0) return 0;
    }
    return 1;
}

int si[12] = {0,  4, 0, 1, 2, 3, 4, 0, 0, 0, 0, 0};
int sj[12] = {0,  0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4};
int di[12] = {1, -1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1};
int dj[12] = {1,  1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0};
int arr[12], sz = 12;

int grid[5][5];

int readFromGrid(int idx)
{
    int res = 0;
    int i = si[idx], j = sj[idx];
    for(int k = 0 ; k < 5 ; k++)
    {
        res *= 11;
        res += grid[i][j];
        i += di[idx];
        j += dj[idx];
    }
    return res;
}

void fillGrid(int idx, int x, int base)
{
    int p = power(base, 4);
    int i = si[idx], j = sj[idx];
    for(int k = 0 ; k < 5 ; k++)
    {
        grid[i][j] = (x / p) % base;
        p /= base;
        i += di[idx];
        j += dj[idx];
    }
}

vector<vector<vector<int> > > sols;

void solve()
{
    if(!sz)
    {
        vector<vector<int> > temp;
        for(int i = 0;  i < 5 ; i++)
        {
            temp.push_back(vector<int>(grid[i], grid[i] + 5));
        }
        sols.push_back(temp);
        return;
    }
    int mn = ne, mnI = 0, bestX;
    for(int i = 0 ; i < sz ; i++)
    {
        int xx = readFromGrid(arr[i]);
        if(deg[xx] < mn)
        {
            mn = deg[xx];
            mnI = i;
            bestX = xx;
        }
    }
    int cur = arr[mnI];
    swap(arr[mnI], arr[--sz]);
    for(int e = head[bestX] ; e ; e = nxt[e])
    {
        int v = to[e];
        fillGrid(cur, v, 10);
        solve();
    }
    fillGrid(cur, bestX, 11);
    swap(arr[mnI], arr[sz++]);
}

int main()
{
    // freopen("prime3.in", "r", stdin);
    // freopen("prime3.out", "w", stdout);
    int sum;
    iota(arr, arr + 12, 0);
    fill((int*)grid, (int*)grid + 5 * 5, 10);
    scanf("%d%d", &sum, grid[0]);
    for(int i = 1e4 ; i < 1e5 ; i++)
    {
        if(sumDig(i) == sum and isPrime(i))
        {
            for(int j = 0 ; j < 32 ; j++)
            {
                int x = i, z = 0, p = 1;
                for(int k = 0 ; k < 5 ; k++)
                {
                    int d = ((j>>k) & 1) ? 10 : x % 10;
                    x /= 10;
                    z += p * d;
                    p *= 11;
                }
                addEdge(z, i);
            }
        }
    }
    solve();
    if(sols.empty()) puts("NONE");
    sort(sols.begin(), sols.end());
    char *sep = "";
    for(auto &sol:sols)
    {
        printf(sep);
        sep = "\n";
        for(auto &row:sol)
        {
            for(auto &e:row)
            {
                printf("%d", e);
            }
            puts("");
        }
    }
    return 0;
}
