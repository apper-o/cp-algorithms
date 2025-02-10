#include <bits/stdc++.h>
#define pb push_back
#define ll long long 
#define gc getchar_unlocked
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 5*1e3+3;
const int INF = 1e9+3;

struct bigint{
	const int d=9;
	const ll base = 1e9;	
	vector<ll> num;
	int n;
	
	bigint (){
		num.pb(0);
		n=1;
	}

	bigint(int m, vector<ll> arr){
		for(int i=0;i<m;i++)
			num.pb(arr[i]);
		n=m;
	}
	
	bigint (ll x) {
		if(x==0)
			num.pb(0);
		while(x)
		{
			num.pb(x%base);
			x/=base;
		}
		n=num.size();
	}
	/* przypisanie wartosci */
	bigint operator = (bigint x){
		num.clear();
		for(int i=0;i<x.n;i++)
			num.pb(x.num[i]);
		n=x.n;
		return *this;
	}
	
	bigint simplify(int m, vector<ll> arr){
		ll carry=0;
		for(int i=0;i<m;i++)
		{
			arr[i]+=carry;
			carry=arr[i]/base;
			arr[i]%=base;
		}
		while(arr.size()>1 && arr.back()==0)
			arr.pop_back();
		m=arr.size();
		return bigint(m, arr);
	}
	
	
	/* dodawanie */
	bigint operator+(bigint x){
		int m = max(n, x.n)+1;
		vector<ll> res(m);
		for(int i=0;i<n;i++)
			res[i]=num[i];
		for(int i=0;i<x.n;i++)
			res[i]+=x.num[i];
		return simplify(n, res);
	}
	
	bigint operator+=(bigint x){
		return *this = *this + x;
	}
	
	bigint operator-(bigint x){
		vector<ll> res(n);
		for(int i=0;i<n;i++)
			res[i]=num[i];
		for(int i=0;i<n;i++)
		{
			if(i<x.n)
				res[i]-=x.num[i];
			if(res[i]<0)
			{
				res[i]+=base;
				res[i+1]--;
			}
		}
		return simplify(n, res);
	}
	
	/* mnożenie */	
	bigint operator * (bigint x){
		int m = n+x.n+1;
		vector<ll> res(m);
		for(int i=0;i<x.n;i++)
		{	
			ll carry=0;
			for(int j=0;j<n;j++)
			{
				ll tmp = num[j]*x.num[i];
				ll t1=tmp/base, t2=tmp%base;
				res[i+j]+=t2+carry;
				carry=t1+res[i+j]/base;
				res[i+j]%=base;
			}
			for(int j=n;j<m;j++)
			{
				res[j]+=carry;
				carry=res[j]/base;
				res[j]%=base;
			}
		}
		return simplify(n, res);
	}
	
	bigint operator *= (bigint x){
		return *this = *this * x;
	}
	
	bigint operator << (int x){
		int m = x+n;
		vector<ll> res(m);
		for(int i=0;i<n;i++)
			res[i+x]=num[i];
		return simplify(m, res);
	}
	
	bigint operator / (bigint x){
		if(n-x.n<0 || (n==x.n && num.back()<x.num.back()))
			return bigint(0);
		bigint a(0);
		int m=n-x.n+1;
		vector<ll> res(m);
		for(int i=m-1;i>=0;i--)
		{
			ll lo=0, hi=base-1;
			while(lo<hi)
			{
				ll mid = lo + (hi-lo+1)/2;
				if(*this < a+(x*bigint(mid))<<i)
					hi=mid-1;
				else
					lo=mid;
			}
			a+=((x*bigint(lo))<<i);
			res[i]=lo;
		}
		return simplify(m, res);
	}
	
	bigint operator % (bigint x){
		return *this - (*this/x)*x;
	}
	
	bigint operator %= (bigint x){
		return *this = *this % x;
	}
	
	bool operator < (bigint x){
		if(n<x.n)
			return true;
		if(n>x.n)
			return false;
		for(int i=n-1;i>=0;i--)
		{
			if(num[i]>x.num[i])
				return false;
			if(num[i]<x.num[i])
				return true;
		}
		return false;
	}
	
	bool operator == (bigint x){
		if(n!=x.n)
			return false;
		for(int i=0;i<n;i++)
			if(num[i]!=x.num[i])
				return false;
		return true;
	}
	
	void print(){
		if(n==0 && num[0]==0)
			cout<<0;
		else
		{
			cout<<num.back();
			for(int i=n-2;i>=0;i--)
			{
				ll x = num[i]/10;
				int dig=1;
				while(x)
				{
					dig++;
					x/=10;
				}
				for(int i=0;i<d-dig;i++)
					cout<<0;
				cout<<num[i];
			}	
		}		
	}
};


int main()
{
	cin.tie(0); ios_base::sync_with_stdio(0);

	ll a = 1e8;
	bigint b(a);
	
	
	b.print();
	

	return 0;
}
