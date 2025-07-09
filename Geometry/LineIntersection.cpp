// Task : CSES Line Segment Intersection
// AC : https://cses.fi/problemset/result/11658197/
 
#include <bits/stdc++.h>
#define pb push_back
#define ll long long 
#define gc getchar_unlocked
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 1e6+3;
const ll INF = 1e18+3; 
 
struct pii{
	ll x, y;
};
 
pii operator - (pii a, pii b){
	return {a.x-b.x, a.y-b.y};
}
 
int n;
pii a, b, c, d;
 
ll cross(pii a, pii b){
	ll tmp = a.x*b.y-a.y*b.x;
	return (tmp==0 ? 0 : tmp>0 ? 1 : -1);
}
 
ll cross(pii a, pii b, pii c){
	return cross(c-a, c-b);
}
 
// checks whether point c is on the ab line
bool ins(int x, pii a, pii b, pii c){
	if(x)
		return false;
	return (min(a.x, b.x)<=c.x && c.x<=max(a.x, b.x) && min(a.y, b.y)<=c.y && c.y<=max(a.y, b.y));
}
 
int main()
{
	cin.tie(0); ios_base::sync_with_stdio(0);
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>a.x>>a.y>>b.x>>b.y>>c.x>>c.y>>d.x>>d.y;
		ll x=cross(a, b, c), y=cross(a, b, d), z=cross(c, d, a), w=cross(c, d, b);
		bool tmp = (ins(x, a, b, c) || ins(y, a, b, d) || ins(z, c, d, a) || ins(w, c, d, b));
		cout<<(tmp || (x*y<0 && z*w<0) ? "YES" : "NO")<<"\n";
	}
	return 0;
}
