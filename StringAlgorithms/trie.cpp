// Task : CSES Word Combinations
// AC : https://cses.fi/problemset/result/11664321/
 
#include <bits/stdc++.h>
#define pb push_back
#define ll long long 
#define gc getchar_unlocked
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 1e6+3;
const ll INF = 1e9+97; 
const int alpha = 27;
const int M = 1e9+7;

int n;
string s, t;
int adj[MAXN][alpha];
vector<int> last(MAXN);
vector<ll> dp(MAXN);
int node=0;

void add()
{
	int v=0;
	for(int i=0;i<t.size();i++)
	{
		int x = t[i]-'a';
		if(!adj[v][x])
			adj[v][x]=++node;
		v=adj[v][x];
	}
	last[v]++;
}

ll get(int id)
{
	ll res=0;
	for(int i=id,v=0;i<s.size();i++)
	{
		int x=s[i]-'a';
		if(!adj[v][x])
			return res;
		v=adj[v][x];
		
		// no. of possible substrings [id, n] is equal to the no. of possible
		// prefixes [id, i] times no. of possible suffixes [i+1, n]

		res=(res+last[v]*dp[i+1])%M;
	}
	return res;
}

int main()
{
	cin.tie(0); ios_base::sync_with_stdio(0);
	cin>>s>>n;
	for(int i=0;i<n;i++)
	{
		cin>>t;
		add();
	}
	dp[s.size()]=1;
	for(int i=s.size()-1;i>=0;i--)
		dp[i]=get(i);
	cout<<dp[0]<<"\n";

	return 0;
}
