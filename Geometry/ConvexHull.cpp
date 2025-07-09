// Task : CSES Convex Hull
// AC : https://cses.fi/problemset/result/11660100/
 
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
  
pii operator + (pii a, pii b){
	return {a.x+b.x, a.y+b.y};
}
 
int n;
vector<pii> arr;
vector<pii> hull;
pii x;
 
ll cross(pii a, pii b){
	ll tmp = a.x*b.y-a.y*b.x;
	return (tmp==0 ? 0 : tmp>0 ? 1 : -1);
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
	{
		cin>>arr[i].x>>arr[i].y;
		if(arr[0].y>arr[i].y || (arr[0].y==arr[i].y && arr[0].x>arr[i].x))
			swap(arr[i], arr[0]);
	}

	// sets start point at the lowest (and leftmost) point
	x = arr[0];
	for(int i=0;i<n;i++)
		arr[i]=arr[i]-x;


	// sort by angle
	sort(arr.begin()+1, arr.end(), [] (pii a, pii b) {
		ll tmp=cross(a, b);
		// tie broken by distance increasing
		if(!tmp)
			return a.x*a.x-b.y*b.y<b.x*b.x-a.y*a.y;
		return tmp>0;
	});
	
	// includes collinear (order of suffix needs to be swapped)
	int i=n-1;
	while(i>=0 && cross(arr[i-1], arr.back())==0)
		i--;
	reverse(arr.begin()+i, arr.end());

	// convex hull
	hull.pb(arr[0]);
	hull.pb(arr[1]);
	for(int i=2;i<n;i++)
	{
		while(hull.size()>=1 && cross(hull[hull.size()-2], hull[hull.size()-1], arr[i])<0)
			hull.pop_back();
		hull.pb(arr[i]);
	}
	// goes back to original
	for(int i=0;i<hull.size();i++)
		hull[i]=hull[i]+x;


	cout<<hull.size()<<"\n";
	for(auto [x, y] : hull)
		cout<<x<<" "<<y<<"\n";
	
	
	return 0;
}
