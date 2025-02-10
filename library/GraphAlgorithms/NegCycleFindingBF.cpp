// Task : CSES : Cycle Finding
// AC : https://cses.fi/problemset/result/12039989/
 
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 5*1e3+3;
const ll INF = 1e18+3;
const int R = (1<<19);
 
struct pii{
	int v;
	ll c;
};
 
int n, m;
vector<pii> adj[MAXN];
vector<ll> dist(MAXN, INF);
vector<int> p(MAXN);
 
void check()
{
	int cnt=0;
	bool rep=1;
	while(rep && cnt<n+2)
	{
		rep=0;
		for(int v=1;v<=n;v++)
		{
			for(auto [u, w] : adj[v])
				if(dist[u]>dist[v]+w)
				{
					dist[u]=dist[v]+w;
					p[u]=v;
					rep=1;
				}
		}
		cnt++;
	}
	if(cnt==n+2)
	{
		cout<<"YES\n";
		vector<int> ans;
		int v;
		for(int j=1;j<=n;j++)
		{
			v=j;
			for(int i=0;i<=n;i++)
				v=p[v];
			if(v)
				break;
		}
		ans.pb(v);
		v=p[v];
		while(v!=ans[0])
		{
			ans.pb(v);
			v=p[v];
		}
		ans.pb(v);
		reverse(ans.begin(), ans.end());
		for(int v : ans)
			cout<<v<<" ";
		cout<<"\n";
		exit(0);
	}
	
}
 
int main()
{
	cin.tie(0); ios_base::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=0,a,b,c;i<m;i++)
	{
		cin>>a>>b>>c;
		adj[a].pb({b, c});
	}
	check();
	cout<<"NO\n";
	return 0;		
}
