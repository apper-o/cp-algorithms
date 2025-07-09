// Task : CSES Point in Polygon
// AC : https://cses.fi/problemset/result/11663080/
 
#include <bits/stdc++.h>
#define pb push_back
#define ll long long 
#define gc getchar_unlocked
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 1e6+3;
const ll INF = 1e9+97; 
 
struct pii{
	ll x, y;
};
 
pii operator - (pii a, pii b){
	return {a.x-b.x, a.y-b.y};
}
 
int n, m;
vector<pii> arr;
pii p, q={0, INF};
 
ll cross(pii a, pii b){
	ll tmp = a.x*b.y-a.y*b.x;
	return (tmp==0 ? 0 : tmp>0 ? 1 : -1);
}
 
ll cross(pii a, pii b, pii c){
	return cross(c-a, c-b);
}
 
// checks whether point c is on the ab line
bool ins(ll x, pii a, pii b, pii c){
	if(x)
		return false;
	return (min(a.x, b.x)<=c.x && c.x<=max(a.x, b.x) && min(a.y, b.y)<=c.y && c.y<=max(a.y, b.y));
}
 
int main()
{
	cin.tie(0); ios_base::sync_with_stdio(0);
	cin>>n>>m;
	arr.resize(n);
	for(int i=0;i<n;i++)
		cin>>arr[i].x>>arr[i].y;
	arr.pb(arr[0]);
 
	// point is inside polygon only if the number of lines a[i]->a[i+1] which intersect p->inf is odd
	for(int i=0;i<m;i++)
	{
		cin>>p.x>>p.y;
		int cnt=0;
		for(int i=0;i<n;i++)
		{
			ll x=cross(arr[i], arr[i+1], p), y=cross(arr[i], arr[i+1], q), z=cross(p, q, arr[i]), w=cross(p, q, arr[i+1]);
			if(ins(x, arr[i], arr[i+1], p))
			{
				cout<<"BOUNDARY\n";
				cnt=-1;
				break;
			}
			cnt+=(x*y<0 && (z*w<0 || z==0));
		}
		if(cnt>=0)
			cout<<(cnt%2 ? "INSIDE" : "OUTSIDE")<<"\n";
	}
	return 0;
}
