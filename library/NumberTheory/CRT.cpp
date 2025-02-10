// Task : Kattis Chinese Remainder
// AC : https://open.kattis.com/submissions/15188404

#include <bits/stdc++.h>
#define pb push_back
#define ll long long 
#define gc getchar_unlocked
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 2*1e5+3;
const ll INF = 1e9+97; 

struct pii{
	ll x, y;
};

ll mod;

// gcd(a, b) = gcd(b, a%b)
// a*x + b*y = b*x' (a-(a/b)*b)*y'
// a*x + b*y = a*y' - (a/b)*b*y' + b*x'
// a*x + b*x = a*y' + b*(x'-(a/b)*y')
// x = y'
// y = x'-(a/b)*y'

pii extgcd(ll a, ll b){
	if(!b)
		return {1, 0};
	pii tmp = extgcd(b, a%b);
	return {tmp.y, tmp.x-(a/b)*tmp.y};
};

ll crt(ll a1, ll a2, ll p1, ll p2)
{	
	// x, y modular inverses of p1 (mod p2), p2 (mod p1);
	auto [x, y] = extgcd(p1, p2);
	if(x<0)
		x+=p2;
	if(y<0)
		y+=p1;
	// not to overflow
	ll a = a1*y%p1; 
	ll b = a2*x%p2; 
	return (a*p2+b*p1)%mod; // x = a1 * y' * p2 + a2 * x' * p1 (mod p1*p2)
}

int main()
{
	cin.tie(0); ios_base::sync_with_stdio(0);
	ll t, a, b, n, m;
	cin>>t;
	while(t--)
	{
		cin>>a>>n>>b>>m;
		mod = n*m;
		ll res = crt(a, b, n, m);
		cout<<res<<" "<<mod<<"\n";
	}
}
