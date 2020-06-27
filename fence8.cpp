/*
TASK: fence8
LANG: C++14
 */
//#pragma GCC optimize ("O3")
#include<bits/stdc++.h>
#define ll long long
#define S second
#define F first

using namespace std;

const int N = 1030;

int n, r, sum = 0, board[N], req[N], cumReq[N];
int nxt[N], prv[N], freq[N], len[N], cntNodes;

void init()
{
    cntNodes = 1;
    nxt[0] = prv[0] = 0;
}

void unCover(int id)
{
    prv[nxt[id]] = nxt[prv[id]] = id;
}

void cover(int id)
{
    prv[nxt[id]] = prv[id];
    nxt[prv[id]] = nxt[id];
}

void add(int f, int l)
{
    freq[cntNodes] = f;
    len[cntNodes] = l;
    prv[cntNodes] = prv[0];
    nxt[cntNodes] = 0;
    unCover(cntNodes++);
}

bool bt(int bId, int ni, int w)
{
    if(w < 0) return 0;
    if(nxt[0] == 0) return 1;
    bool f = 0, ret = 0;
    for(int i = ni ; i and !ret ; i = prv[i])
    {
        if(board[bId] >= len[i])
        {
            f = 1;
            if(!--freq[i]) cover(i);
            board[bId] -= len[i];
            ret = bt(bId, freq[i] ? i : prv[i], w);
            board[bId] += len[i];
            if(!freq[i]++) unCover(i);
        }
    }
    if(!f) return bt(bId + 1, prv[0], w - board[bId]);
    return ret;
}

bool ok(int r)
{
    int tFreq[129] = {};
    for(int i = 0 ; i < r ; i++) tFreq[req[i]]++;
    init();
    for(int i = 0 ; i < 129 ; i++) if(tFreq[i]) add(tFreq[i], i);
    return bt(0, prv[0], sum - cumReq[r - 1]);
}

int main()
{
    freopen("fence8.in", "r", stdin);
    freopen("fence8.out", "w", stdout);
    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++) scanf("%d", board + i), sum += board[i];
    sort(board, board + n);
    scanf("%d", &r);
    for(int i = 0 ; i < r ; i++) scanf("%d", req + i);
    sort(req, req + r);
    int temp = 0;
    for(int i = 0 ; i < r ; i++)
    {
        cumReq[i] = temp += req[i];
    }
    int s = 0, e = r;
    while(s < e)
    {
        int mid = s + (e - s + 1) / 2;
        if(ok(mid)) s = mid;
        else e = mid - 1;
    }
    printf("%d\n", s);
    return 0;
}
