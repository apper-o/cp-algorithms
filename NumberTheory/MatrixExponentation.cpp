// Task : CSES Graph Paths
// AC : https://cses.fi/problemset/result/11898451/

#include <bits/stdc++.h>
#define pb push_back
#define ll long long 
#define gc getchar_unlocked
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 100+3;
const int M = 1e9+7;

struct mat{
	ll m[MAXN][MAXN];	
	mat() {
		memset(m,0,sizeof(m));
	}
};

int n, m, k;
mat adj;

mat operator * (mat a, mat b){
	mat res;
	for(int i=1;i<=n;i++)
		for(int k=1;k<=n;k++)
			for(int j=1;j<=n;j++)
				res.m[i][j]=(res.m[i][j]+a.m[i][k]*b.m[k][j])%M;
	return res;
}

// matrix a^b
mat expo(mat a, int b)
{
	mat res;
	for(int i=1;i<=n;i++)
		res.m[i][i]=1;
	while(b)
	{
		if(b%2)
			res=res*a;
		a=a*a;
		b/=2;
	}
	return res;
}

int main()
{
	cin.tie(0); ios_base::sync_with_stdio(0);
	cin>>n>>m>>k;
	for(int i=0,a,b;i<m;i++)
	{
		cin>>a>>b;
		adj.m[a][b]++;
	}
	adj=expo(adj, k);
	cout<<adj.m[1][n]<<"\n";
	return 0;
}
