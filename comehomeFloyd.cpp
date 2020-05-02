/*
TASK: comehome
LANG: C++14
*/

#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int N  = 200 + 5, M = 4e6 + 5;

int mat[N][N], n;

void floyd()
{
    for(int k = 0 ; k < n ; k++)
    {
        for(int i = 0 ; i < n ; i++)
        {
            for(int j = 0 ;  j < n ; j++)
            {
                mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
            }
        }
    }
}

int main()
{
    freopen("comehome.in", "r", stdin);
    freopen("comehome.out", "w", stdout);
    memset(mat, 0x3f, sizeof mat);
    n = 128;
    int m, c;
    char u, v;
    scanf("%d", &m);
    while(m--)
    {
        scanf(" %c %c%d", &u, &v, &c);
        mat[u][v] = mat[v][u] = min(mat[v][u], c);
    }
    floyd();
    char res = min_element(mat['Z'] + 'A', mat['Z'] + 'Z') - mat['Z'];
    printf("%c %d\n", res, mat['Z'][res]);
    return 0;
}
