/*
TASK: betsy
LANG: C++14
 */
//#pragma GCC optimize ("O3")
#include<bits/stdc++.h>
#define ll long long
#define S second
#define F first

using namespace std;

const int N = 151, M = 24226;

int noUnVisited, ans = 0, cnt[9][9];
bool vis[9][9];

void visit(int i, int j, bool v)
{
    vis[i][j] = v;
    int di = 0, dj = 1;
    for(int k = 0 ; k < 4 ; k++)
    {
        int ni = i + di;
        int nj = j + dj;
        if(ni >= 0 and ni < 9 and nj >= 0 and nj < 9)
        {
            cnt[ni][nj] -= 2 * v - 1;
        }
        swap(di, dj);
        if(k == 1) di *= -1, dj *= -1;
    }
    noUnVisited -= 2 * v - 1;
}

void printCnt(int n)
{
    for(int i = 1 ; i <= n ; i++)
    {
        for(int j = 1 ; j <= n ; j++)
        {
            cout << cnt[i][j] <<" ";
        }
        puts("");
    }
    fflush(stdout);
}

void solve(int i, int j)
{
    if(i == 1 and j == 1)
    {
        ans += !(noUnVisited);
        return;
    }
    int di = 0, dj = 1, cnt1 = 0, nxtI, nxtJ;
    for(int k = 0 ; k < 4 ; k++)
    {
        int ni = i + di;
        int nj = j + dj;
        if(!vis[ni][nj])
        {
            if(cnt[ni][nj] == 1 and (ni != 1 or nj != 1))
            {
                cnt1++;
                nxtI = ni;
                nxtJ = nj;
            }
        }
        swap(di, dj);
        if(k == 1) di *= -1, dj *= -1;
    }
    if(cnt1 > 1) return;
    if(cnt1 == 1) return visit(nxtI, nxtJ, 1), solve(nxtI, nxtJ), visit(nxtI, nxtJ, 0);
    for(int k = 0 ; k < 4 ; k++)
    {
        int ni = i + di;
        int nj = j + dj;
        if(!vis[ni][nj])
        {
            visit(ni, nj, 1);
            solve(ni, nj);
            visit(ni, nj, 0);
        }
        swap(di, dj);
        if(k == 1) di *= -1, dj *= -1;
    }
}

int main()
{
    // freopen("betsy.in", "r", stdin);
    // freopen("betsy.out", "w", stdout);
    int n;
    for(int i = 0 ; i < 9 ; i++)
    {
        for(int j = 0 ; j < 9 ; j++) cnt[i][j] = 4;
    }
    scanf("%d", &n);
    noUnVisited = (n + 2) * (n + 2);
    for(int i = 0 ; i <= n + 1 ; i++)
    {
        for(int j = 0 ; j <= n + 1 ; j++)
        {
            if(!i or !j or i == n + 1 or j == n + 1) visit(i, j, 1);
        }
    }
    visit(n, 1, 1);
    solve(n, 1);
    printf("%d\n", ans);
    return 0;
}
