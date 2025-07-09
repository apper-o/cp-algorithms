// Task : CSES : Shortest Routes I
// AC : https://cses.fi/problemset/result/12039558/
 
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 2*1e5+3;
const ll INF = 1e9+3;
const int R = (1<<19);
 
struct pii{
	int v;
	ll c;
};
 
int n, m;
vector<pii> adj[MAXN];
ll dist[MAXN];
 
class cmp{
	public:
	bool operator () (pii a, pii b) {
		return !(a.c<b.c);
	}
};
 
priority_queue<pii, vector<pii>, cmp> q;
 
int main()
{
	cin.tie(0); ios_base::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=0,a,b,c;i<m;i++)
	{
		cin>>a>>b>>c;
		adj[a].pb({b, c});
	}
	memset(dist,0x3f,sizeof(dist));
	dist[1]=0;
	q.push({1, 0});
	while(q.size())
	{
		auto [v, c] = q.top();
		q.pop();
		if(c>dist[v])
			continue;
		for(auto [u, w] : adj[v])
			if(dist[u]>dist[v]+w)
			{
				dist[u]=dist[v]+w;
				q.push({u, dist[u]});
			}
	}
	for(int i=1;i<=n;i++)
		cout<<dist[i]<<" ";
	return 0;		
}
