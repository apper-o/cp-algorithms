#include <bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 6*1e5+3;
const ll INF = 1e18;

struct pii{
	ll x, y;
};

int n;
vector<pii> arr;
ll res=INF;

ll d(pii a, pii b){
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

void get(vector<pii> a)
{
	for(int i=0;i<a.size();i++)
		for(int j=i+1;j<a.size() && (a[j].y-a[i].y)*(a[j].y-a[i].y)<=res;j++)
			res = min(res, d(a[i], a[j]));
}

void solve(int a, int b)
{
	if(b-a+1<=3)
	{
		for(int i=a;i<b;i++)
			for(int j=i+1;j<=b;j++)
				res=min(res, d(arr[i], arr[j]));
	}
	int mid = (a+b)/2;
	int x = (arr[mid].x+arr[mid+1].x)/2; 
	vector<pii> tmp;
	for(int i=a;i<=b;i++)
		if((arr[i].x-x)*(arr[i].x-x)<=res)
			tmp.pb(arr[i]);
	sort(tmp.begin(), tmp.end(), [] (pii a, pii b){
		return a.y<b.y;
	});
	get(tmp);
}

int main()
{
	cin.tie(0); ios_base::sync_with_stdio(0);
	cin>>n;
	arr.resize(n);
	for(int i=0;i<n;i++)
		cin>>arr[i].x>>arr[i].y;
	sort(arr.begin(), arr.end(), [] (pii a, pii b){
		return a.x<b.x;
	});
	solve(0, n-1);
	cout<<(float)res<<"\n";
}
