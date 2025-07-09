// Task : SPOJ Digit Sum
// AC : https://www.spoj.com/status/PR003004,apper/


#include <bits/stdc++.h>
#define pb push_back
#define ll long long 
#define gc getchar_unlocked
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 20+3;
const int INF = 1e9+3;

int n;
ll dp[20][2][145];
string x;

ll get(int it, bool exc, int sum)
{
	if(it==x.size())
		return sum;
	if(dp[it][exc][sum]==-1)
	{
		dp[it][exc][sum]=0;
		int lim = (exc ? x[it]-'0' : 9);
		for(int i=0;i<=lim;i++)
			dp[it][exc][sum]+=get(it+1, exc&(lim==i), sum+i);
	}
	return dp[it][exc][sum];
}

ll solve(string s)
{
	if(s=="-1")
		return 0;
	x=s;
	memset(dp,-1,sizeof(dp));
	return get(0, 1, 0);
}

int main()
{
	cin.tie(0); ios_base::sync_with_stdio(0);
	cin>>n;
	for(int i=0;i<n;i++)
	{
		memset(dp,-1,sizeof(dp));
		ll a, b;
		cin>>a>>b;
		cout<<solve(to_string(b))-solve(to_string(a-1))<<"\n";
	}


	return 0;
}
