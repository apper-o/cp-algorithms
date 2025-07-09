// Task : YOSUPO Primality Test
// AC : https://judge.yosupo.jp/submission/260401

#include <bits/stdc++.h>
#define pb push_back
#define ll long long 
#define gc getchar_unlocked
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 2*1e5+3;
const ll INF = 1e9+97; 

int q;
mt19937 rng(time(0));

// n-1 = 2^r * d (with d odd)
// a rng() which belongs to [1, n-1]
// for n to be prime for every number a must hold
// a^(n-1) == 1 (mod n)
// a^(2^r*d) - 1 == 0 (mod n)
// (a^(2*(r-1)*d)+1)(a^(2^(r-2)*d)+1) ... (a^d-1) == 0 (mod n) 

ll expo(ll base, ll b, ll mod)
{
	ll res=1;
	while(b)
	{
		if(b%2)
			res=(__int128)res*base%mod;
		base=(__int128)base*base%mod;
		b/=2;
	}
	return res;
}

bool check(ll n, ll r, ll d)
{
	ll a=rng()%(n-1)+1;
	ll x = expo(a, d, n);
	// a^(n-1) == -1 (mod n)  =>  a^(n-1) == n-1 (mod n)  ==> a^n == -1 * -1 = 1 (mod n)
	// found a^d+1 == 0 (mod n) or a^d-1 == 0 (mod n)
	if(x==1 || x==n-1)
		return true;
	for(int i=1;i<r;i++)
	{
		x=(__int128)x*x%n;
		// won't hold for any (a^(2^(r-k)*d)+1) k in [0, r] (because next rep is also 1)
		if(x==1)
			return false;
		// found a^(2^i*d+1) == 0 (mod n)
		if(x==n-1)
			return true;
	}
	// doesnt hold for any (a^(2^(r-k)*d)+1) k in [0, r]
	return false;
}

bool prime(ll n)
{
	if(n<5)
		return (n==2) || (n==3);
	if(n%2==0)
		return false;
	ll r=0, d=n-1;
	while(d%2==0)
	{
		d/=2;
		r++;
	}
	for(int i=0;i<30;i++)
		if(!check(n, r, d))
			return false;
	return true;
}

int main()
{
	cin.tie(0); ios_base::sync_with_stdio(0);
	cin>>q;
	while(q--)
	{
		ll n;
		cin>>n;
		cout<<(prime(n) ? "Yes" : "No")<<"\n";
	}
	return 0;
}
