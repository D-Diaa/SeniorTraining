/*
TASK: comehome
LANG: C++14
*/
#include <bits/stdc++.h>
#include <ext/numeric>
#define ll long long

using namespace std;
using namespace __gnu_cxx;

const int N  = 200 + 5, M = 4e6 + 5;

typedef vector<vector<int> > mat;

int n;

struct Mul
{
     mat operator()(const mat& a, const mat& b)const
     {
         mat ret(a.size(), vector<int>(b[0].size()));
         for(int i = 0 ; i < ret.size() ; i++)
         {
             for(int j = 0 ; j < ret[i].size() ; j++)
             {
                 ret[i][j] = min(a[i][j], b[i][j]);
                 for(int k = 0 ; k < a[0].size() ; k++)
                 {
                     ret[i][j] = min(ret[i][j], a[i][k] + b[k][j]);
                 }
             }
         }
         return ret;
     }
};

mat identity_element(const Mul&)
{
    mat ret(n, vector<int>(n, 0x3f3f3f3f));
    for(int i = 0 ; i < n ; i++) ret[i][i] = 0;
    return ret;
}

int main()
{
    freopen("comehome.in", "r", stdin);
    freopen("comehome.out", "w", stdout);
    n = 128;
    mat Mat(n, vector<int>(n, 0x3f3f3f3f));
    int m, c;
    char u, v;
    scanf("%d", &m);
    while(m--)
    {
        scanf(" %c %c%d", &u, &v, &c);
        Mat[u][v] = Mat[v][u] = min(Mat[v][u], c);
    }
    Mat = power(Mat, n, Mul());
    char res = min_element(Mat['Z'].begin() + 'A', Mat['Z'].begin() + 'Z') - Mat['Z'].begin();
    printf("%c %d\n", res, Mat['Z'][res]);
    return 0;
}
