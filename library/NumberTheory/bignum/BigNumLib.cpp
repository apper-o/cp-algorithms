#include <bits/stdc++.h>
#define pb push_back
#define ll long long 
#define gc getchar_unlocked
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 2*1e4+3;
const ll INF = 1e9+3;

struct bignum
{
	vector<ll> num;
	const int base=1e9;
	
	// ################### build ################### // 
	bignum (){};
	
	bignum (ll a){
		if(a==0)
			num.pb(0);
		while(a)
		{
			num.pb(a%base);
			a/=base;
		}
	}
	
	bignum (const vector<ll> &arr){
		num=arr;
	}

	bignum (const vector<ll> &arr, const int &a, const int &b){
		num.clear();
		for(int i=a;i<b;i++)
			num.pb(arr[i]);
		while(num.size() && num.back()==0)
			num.pop_back();
		if(num.empty())
			num.pb(0);
	}

	vector<ll> shrink(vector<ll> arr){
		while(arr.size()>1 && arr.back()==0)
			arr.pop_back();
		return arr;
	}
	
	bignum operator = (const bignum &x){
		vector<ll> arr;
		for(int i=0;i<x.num.size();i++)
			arr.pb(x.num[i]);
		while(arr.size()>1 && arr.back()==0)
			arr.pop_back();
		num=arr;
		return bignum(arr);
	}
	// ############################################# // 

	// ################ bit shift ################# // 
	bignum operator << (const int x)
	{
		int n = num.size();
		vector<ll> arr(n+x);
		for(int i=n-1;i>=0;i--)
			arr[i+x]=num[i];
		return bignum(shrink(arr));
	}
	bignum operator >> (const int x)
	{
		int n = num.size();
		vector<ll> arr(max(1, n-x));
		for(int i=0;i+x<n;i++)
			arr[i]=num[i+x];
		return bignum(shrink(arr));
	}
	// ############################################# // 
	
	// ############### addition #################### // 
	bignum operator + (const bignum &x){
		int n = num.size(), m=x.num.size();
		vector<ll> arr(max(n, m)+1);
		for(int i=0;i<m;i++)
			arr[i]=x.num[i];
		for(int i=0;i<n;i++)
		{
			arr[i]+=num[i];
			arr[i+1]+=arr[i]/base;
			arr[i]%=base;
		}
		return bignum(shrink(arr));
	}
	
	bignum operator += (const bignum &x){
		return *this = *this + x;
	};
	// ############################################# // 
	
	
	
	// ############### subtraction ################ // 
	bignum operator - (const bignum &x){
		int n = num.size(), m=x.num.size();
		vector<ll> arr(n+1);
		for(int i=0;i<m;i++)
			arr[i]=num[i]-x.num[i];
		for(int i=0;i<n;i++)
			if(arr[i]<0)
			{
				arr[i+1]--;
				arr[i]+=base;
			}
		return bignum(shrink(arr));
	}
	
	bignum operator -= (const bignum &x){
		return *this = *this - x;
	}
	// ############################################# // 

	
	// ######### karatsuba multiplication ########## // 
	bignum operator * (bignum xn){
	
		int n = max((int)num.size(), (int)xn.num.size());
		if(min(num.size(), xn.num.size())==1)
		{
			vector<ll> arr(n+3);
			bignum c = (num.size()>xn.num.size() ? num : xn.num);
			ll d = (num.size()>xn.num.size() ? xn.num[0] : num[0]);
			for(int i=0;i<n;i++)
				arr[i]=c.num[i]*d;
			for(int i=0;i<n+2;i++)
			{
				arr[i+1]+=arr[i]/base;
				arr[i]%=base;
			}
			return bignum(shrink(arr));			
		}

		bignum ah(num, n/2, n);
		bignum al(num, 0, n/2);
		bignum bh(xn.num, n/2, n);
		bignum bl(xn.num, 0, n/2);

		
		bignum x = ah*bh;
		bignum z = al*bl;
		bignum y = (ah+al)*(bh+bl)-x-z;
		
		// formula : a * b = (ah*bh) * base^n + ((ah+al)(bh+bl)-(ah*bh)(al*bl)) * base^(n/2) + al*bl
		return (x<<n) + (y<<(n/2)) + z; 
	}
	
	bignum operator *= (const bignum &x){
		return *this = *this * x;
	}
	// ############################################# // 
	
	
	// ########## division (using bs) ############## // 
	bignum operator / (bignum x){
		int n = num.size(), m = x.num.size();
		int rep=max(0, n-m+1);
		vector<ll> arr(rep+2);
		// res keeps track of the current product 
		bignum res(0);
		for(int i=rep-1;i>=0;i--)
		{
			// binary search for multiply such that res+((x*mid)<<i) is lesser than num *this
			int lo=0, hi=base-1;
			while(lo<hi)
			{
				int mid = lo + (hi-lo+1)/2;
				if(*this < res + ((bignum(mid) * x)<<i))
					hi=mid-1;
				else
					lo=mid; 
			}
			arr[i]=lo;
			res+=((bignum(lo)*x)<<i);
		}
		return shrink(arr);
	}
	
	bignum operator /= (const bignum &x){
		return *this = *this / x;
	}
	// ############################################# // 
	
	
	// ############## comparators ################# // 
	bool operator > (const bignum &x){
		int n = num.size(), m=x.num.size();
		if(n>m)	return true;
		if(n<m)	return false;
		for(int i=n-1;i>=0;i--)
			if(num[i]!=x.num[i])
				return (num[i]>x.num[i]);
		return false;
	}
	bool operator >= (const bignum &x){
		int n = num.size(), m=x.num.size();
		if(n>m)	return true;
		if(n<m)	return false;
		for(int i=n-1;i>=0;i--)
			if(num[i]!=x.num[i])
				return (num[i]>x.num[i]);
		return true;
	}
	bool operator < (const bignum &x){
		int n = num.size(), m=x.num.size();
		if(n>m)	return false;
		if(n<m)	return true;
		for(int i=n-1;i>=0;i--)
			if(num[i]!=x.num[i])
				return (num[i]<x.num[i]);
		return false;
	}
	bool operator <= (const bignum &x){
		int n = num.size(), m=x.num.size();
		if(n>m)	return false;
		if(n<m)	return true;
		for(int i=n-1;i>=0;i--)
			if(num[i]!=x.num[i])
				return (num[i]<x.num[i]);
		return true;
	}
	// ############################################# // 
	
	void print(){
		int n = num.size();
		cout<<num[n-1];
		for(int i=n-2;i>=0;i--)
		{
			int d = to_string(num[i]).size();
			for(int j=0;j<9-d;j++)
				cout<<0;
			cout<<num[i];
		}	
		cout<<"\n";	
	}
};

int main()
{
	bignum a = 123456789;
	bignum b = 10000;
	a*=a;
	a.print();
	a*=a;
	a.print();
	a+=a;
	a.print();

	bignum tmp = a/b;
	tmp.print();
	
	bignum(b*tmp).print();
	
	return 0;
}

