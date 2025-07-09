// Task : CSES Point Location Test
// AC : https://cses.fi/problemset/result/11657976/
 
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
pii a, b, c;
 
ll cross(pii a, pii b){
	return a.x*b.y-a.y*b.x;
}
 
ll cross(pii a, pii b, pii c){
	return cross(c-a, c-b);
}
 
int main()
{
	cin.tie(0); ios_base::sync_with_stdio(0);
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>a.x>>a.y>>b.x>>b.y>>c.x>>c.y;
		ll tmp = cross(a, b, c);
		cout<<(tmp==0 ? "TOUCH" : tmp>0 ? "LEFT" : "RIGHT")<<"\n";
	}
	return 0;
}
