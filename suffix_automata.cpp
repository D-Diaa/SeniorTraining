#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+5, M=2*N, alpha=256;

#define arr(t, n, s, e) t _##n[e-s+1], *n= _##n+(-s);

typedef map<unsigned char, int> mpci;
typedef vector<int> vi;
typedef pair<int, unsigned char> pic;

arr(mpci, child, -1, M);
arr(int, fail, -1, M);
arr(int, len, -1, M);
arr(unsigned char, str, 0, N);
arr(unsigned char, buff, 0, N);
arr(int, firstPos, 0, N);
arr(bool, isClone, 0, N);
arr(pic, parent, 0, N);
arr(vi, invFail, 0, N);
arr(long long, dp, 0, N);
arr(long long, cnt, 0, N);
arr(int, vis, 0, N);

int last, nNodes, vid = 1;

int addNode()
{
    child[nNodes].clear();
//    fail[nNodes]=len[nNodes]=-1;
    return nNodes++;
}

void addEdge(int f, int t, unsigned char c)
{
    child[f][c]=t;
}
void init()
{
    nNodes = last = 0;
    addNode();
    len[0] = 0;
    fail[0] = -1;
    len[-1] = -1;
    for(int i=0; i<alpha; i++)
    {
        addEdge(-1, 0, (unsigned char)i);
    }
}

void addChar(unsigned char c)
{
    int p, cur = addNode();
    parent[cur]={last, c};
    // Extend
    len[cur] = len[last]+1;
    isClone[cur] = false;
    firstPos[cur] = len[last];
    bool flag;
    map<unsigned char,int>::iterator x;
    // Check for fail links of P, if they have the character and add till fail to add
    for(p = last ; tie(x, flag) = child[p].emplace(c, cur), flag ; p = fail[p]) ;
    int q = x->second; // Next node after fail to add
    if(len[p]+1 == len[q]) fail[cur] = q; // p on the longest path between root and q
    else
    {
        // Clone the node to split the paths
        int clone = addNode();
        len[clone]=len[p]+1;
        child[clone] = child[q];
        fail[clone] = fail[q];
        isClone[clone] = true;
        firstPos[clone] = firstPos[q];
        parent[clone] = {p, c};

        // All smaller suffixes of p that originally went to q --> go to clone
        for(; ~p; p = fail[p])
        {
            int &ch = child[p][c];
            if(ch!=q) break;
            ch = clone;
        }
        // q fails to clone (clone smaller than q with the same suffix)
        fail[q] = fail[cur] = clone;
    }
    last = cur;
}

void print()
{
    for(int i=0; i<nNodes; i++)
    {
        printf("%d %d fail__\n", i, fail[i]);
        for(auto ch: child[i])
            printf("%d %d %c\n", i, ch.second, ch.first);
    }
    puts("_______________________________");
    fflush(stdout);
}

void build(unsigned char * str)
{
    init();
    for(;*str;str++)
        addChar(*str);

    for(int i=1; i<nNodes; i++)
        invFail[fail[i]].push_back(i);
}

bool checkPattern(unsigned char * patt)
{
    for(int cur =0; *patt; patt++){
        auto it = child[cur].find(*patt);
        if(it==child[cur].end()) return false;
        cur = it->second;
    }
    return true;
}

long long countDistinct(int cur)
{
    long long & ret = dp[cur];
    if(vis[cur]==vid) return ret;
    ret = 1;
    vis[cur] = vid;
    for(auto ch:child[cur])
        ret+=countDistinct(ch.second);
    return ret;
}

string kThDistinctSubstring(int cur, int k, string pre)
{
    if(!--k)
        return pre;
    for(auto & ch:child[cur])
    {
        if(k > countDistinct(ch.second))
            k-=countDistinct(ch.second);
        else
        {
            return kThDistinctSubstring(ch.second, k, pre+(char)ch.first);
        }
    }
    return "";
}

// Minimum number of single character rotations for lex-smallest
int minRotations(unsigned char * str)
{
    int n = strlen((char*)str);
    memcpy(str+n, str, n);
    str[2*n]=0;
    build(str);
    int ret = 0, cur = 0;
    while(not child[cur].empty())
    {
        ret++;
        cur = child[cur].begin()->second;
    }
    return 2*n-ret;
}

long long fillCount(int cur)
{
    long long & ret = cnt[cur];
    if(vis[cur]==vid)return ret;
    vis[cur]=vid;
    for(auto & ch:child[cur])
        ret+=fillCount(ch.second);
    return ret;
}

void initCount()
{
    memset(cnt, 0, nNodes*sizeof(cnt[0]));
    // Label final nodes
    for(int cur = last; ~cur; cur=fail[cur])
        cnt[cur] = 1;
    ++vid;
    // Count paths from node to "final" nodes
    fillCount(0);
}

long long findNoOccurrences(unsigned char * patt)
{
    int cur;
    for(cur =0; *patt; patt++){
        auto it = child[cur].find(*patt);
        if(it==child[cur].end()) return 0;
        cur = it->second;
    }
    return fillCount(cur);
}

int firstOccurrence(unsigned char * patt)
{
    int cur, ret=1;
    for(cur =0; *patt; patt++){
        auto it = child[cur].find(*patt);
        if(it==child[cur].end()) return -1;
        cur = it->second;
        ret--;
    }
    return firstPos[cur]+ret;
}

void allOccurrences(int cur, int pLen, vector<int>& occurrences)
{
    if(not isClone[cur]) occurrences.push_back(firstPos[cur]-pLen+1);
    for(auto u: invFail[cur]) allOccurrences(u, pLen, occurrences);
}

void printAllOccurrences(unsigned char * patt)
{
    int cur, pLen=0;
    // Find first occurrence
    for(cur =0; *patt; patt++){
        auto it = child[cur].find(*patt);
        // If none, return
        if(it==child[cur].end()) return puts(""), void();
        pLen++;
        cur = it->second;
    }
    // Else, recurse over inverse fail links starting from first
    vector<int> occurrences;
    allOccurrences(cur, pLen, occurrences);
    for(auto occ: occurrences) printf("%d ", occ);
    puts("");
}

long long minNonAppearing(int cur)
{
    long long &ret = dp[cur];
    if(vis[cur]==vid) return ret;
    // TODO: alpha here is assumed to be 26 for alphabets only
    if(child[cur].size()!=26) return ret = 1;
    ret = LONG_LONG_MAX;
    for(auto ch: child[cur])
    {
        ret = min(ret, minNonAppearing(ch.second));
    }
    return ++ret;
}

string buildLexiSmallestNonAppearing(int cur, const string & pre)
{
    long long ret = minNonAppearing(cur);
    if(child[cur].size()!=26)
    {
        // TODO: alpha here is assumed to be 26 for alphabets only
        for(char i='a'; i<='z'; i++)
            if(not child[cur].count(i))
                return pre+i;
    }
    for(auto ch: child[cur])
    {
        if(ret == 1 + minNonAppearing(ch.second))
        {
            return buildLexiSmallestNonAppearing(ch.second, pre+(char)ch.first);
        }
    }
    return "";
}

void lcs(unsigned char * str1, unsigned char* str2)
{
    build(str1);
    int cur = 0, max_len=0;
    unsigned char * temp;
    int l=0;
    map<unsigned char, int>::iterator it;
    for(; *str2; str2++)
    {
        while(it=child[cur].find(*str2), it==child[cur].end())
            cur=fail[cur], l=len[cur];
        cur = it->second;
        l++;
        if(l>max_len)
        {
            max_len=l;
            temp = str2+1-max_len;
        }
    }
    unsigned char c = temp[max_len];
    temp[max_len]=0;
    puts((char*)temp);
    temp[max_len]=c;
}

int maxLen, best;
long long lcs_coach_dfs (int cur)
{
    long long & ret =dp[cur];
    if(vis[cur]==vid) return ret;
    vis[cur] = vid;
    ret = 0;
    for(auto & ch: child[cur])
    {
        switch(ch.first)
        {
            case 'Z'+1:
                ret|=1;
                break;
            case 'Z'+2:
                ret|=2;
                break;
            default:
                ret|= lcs_coach_dfs(ch.second);
                break;
        }
    }
    if(ret==3 and len[cur]>maxLen)
        maxLen = len[cur], best=cur;
    return ret;
}

void printPre(int cur)
{
    if(cur){
        printPre(parent[cur].first);
        printf("%c", parent[cur].second);
    }
}

void lcs_coach(unsigned char * str)
{
    build(str);
    ++vid;
    lcs_coach_dfs(0);
    printPre(best);
    puts("");
}

int m, mx;
vector<int> best_ind;
bitset<100> mem[M];

bitset<100> lifeforms_dfs(int cur)
{
    bitset<100> & ret = mem[cur];
    if(vis[cur]==vid) return ret;
    vis[cur] = vid;
    ret.reset();
    for(auto ch: child[cur])
    {
        if(ch.first>=128)
            ret[ch.first-128]=true;
        else
            ret|=lifeforms_dfs(ch.second);
    }
    if(2*ret.count()>m and len[cur]>mx) best_ind.clear(), mx=len[cur];
    if(2*ret.count()>m and len[cur]==mx and mx) best_ind.emplace_back(cur);
    return ret;
}

void solve_lifeforms()
{
    char *s = (char*)str;
    for(int i = 0 ; i < m ; i++)
    {
        scanf("%s", s);
        s+=strlen(s);
        *s++ = 128 + i;
    }
    if(m == 1)
    {
        *--s = 0;
        puts((char*)str);
        return;
    }
    *s = 0;
    ++vid;
    best_ind.clear();
    mx = 0;
    build(str);
    lifeforms_dfs(0);
    if(best_ind.empty()) puts("?");
    else
    {
        for(auto i:best_ind) printPre(i), puts("");
    }
}


int main()
{
#ifdef clion
    freopen("test.in", "r", stdin);
#endif
    bool f = true;
    while(scanf("%d", &m), m)
    {
        if(f) f = false;
        else puts("");
        solve_lifeforms();
    }
    return 0;
}
