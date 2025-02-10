// Task : Minimum Euclidean Distance
// AC : https://cses.fi/problemset/result/11660305/
 
#include <bits/stdc++.h>
#define pb push_back
#define ll long long 
#define gc getchar_unlocked
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 1e6+3;
const ll INF = 8e18+97; 
 
struct pii{
	ll x, y;
};
 
pii operator - (pii a, pii b){
	return {a.x-b.x, a.y-b.y};
}
  
pii operator + (pii a, pii b){
	return {a.x+b.x, a.y+b.y};
}
 
bool operator < (pii a, pii b){
	return {a.y==b.y ? a.x<b.x : a.y<b.y};
};
 
int n;
vector<pii> arr;
ll ans=INF;
queue<pii> q;
set<pii> s;

int main()
{
	cin.tie(0); ios_base::sync_with_stdio(0);
	cin>>n;
	arr.resize(n);
	for(int i=0;i<n;i++)
		cin>>arr[i].x>>arr[i].y;
		
	// sorts points by x 
	sort(arr.begin(), arr.end(), [] (pii a, pii b) {
		if(a.x==b.x)
			return a.y<b.y;
		return a.x<b.x;
	});

	// Sweep Line - remembers only those points which distance is lower than ans  
	s.insert(arr[0]);
	q.push(arr[0]);	
	for(int i=1;i<n;i++)
	{
		auto [x, y] = arr[i];
		while(q.size() && (x-q.front().x)*(x-q.front().x)>=ans)
		{
			s.erase(q.front());
			q.pop();
		}	
		
		// lower bound for points in range [y-ans, y+ans] 
		// there is no sense in checking the rest because (y-yp)*(y-yp) >= ans
		auto b = s.lower_bound((pii){0, y-ans});
		auto e = s.lower_bound((pii){0, y+ans});
		for(auto it=b;it!=e;it++)
		{
			auto [xp, yp] = *it;
			ans=min(ans, (xp-x)*(xp-x)+(yp-y)*(yp-y));
		}
		s.insert(arr[i]);
		q.push(arr[i]);
	}
	cout<<ans<<"\n";
	return 0;
}
