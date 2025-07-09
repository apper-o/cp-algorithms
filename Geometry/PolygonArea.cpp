// Task : CSES Polygon Area
// AC : https://cses.fi/problemset/result/11658264/
 
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
vector<pii> arr;
ll res=0;

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
	arr.resize(n);
	for(int i=0;i<n;i++)
		cin>>arr[i].x>>arr[i].y;
	// SHOELACE FORMULA
	// the area of the polygon is the sum over the areas of trapezoids inside the polygon
	// a[i].x > a[i+1].x -> add
	// a[i].x < a[i+1].x -> remove
	// to simplify use cross product  
	for(int i=0;i<n-1;i++)
		res+=cross(arr[i], arr[i+1]);
	res+=cross(arr[n-1], arr[0]);
	cout<<abs(res)<<"\n";
	return 0;
}
