// Task : CF Maximum Product
// AC : https://codeforces.com/gym/100886/submission/301648145

#include <bits/stdc++.h>
#define pb push_back
#define ll long long 
#define gc getchar_unlocked
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 5*1e3+3;
const int INF = 1e9+3;

string a, b;
ll dp[20][2][2];
ll nxt[20][2][2];

ll get(int it, bool exc, bool sub, bool real)
{
	if(it==b.size())
		return 1;
	if(dp[it][exc][sub]==-1)
	{
		int up = (exc ? b[it]-'0' : 9), low = (sub ? a[it]-'0' : 1);
		for(int dig=max(low, (int)real);dig<=up;dig++)
		{
			ll tmp = get(it+1, exc&(dig==up), sub&(dig==low), real|dig)*max(dig, 1);
			
			if(dp[it][exc][sub]<tmp)
			{
				dp[it][exc][sub]=tmp;
				nxt[it][exc][sub]=dig;
			}
		}
	}
	return dp[it][exc][sub];
}

void solve()
{
	memset(dp,-1,sizeof(dp));
	memset(nxt,-1,sizeof(nxt));
	int it=0, exc=1, sub=1, dig;
	get(it, exc, sub, 0);
	ll res=0;
	if(dp[it][exc][sub]<=0)
	{
		cout<<a<<"\n";
		exit(0);
	}
	while((dig=nxt[it][exc][sub])!=-1)
	{
		res=res*10+dig;
		exc&=(dig==b[it]-'0');
		sub&=(dig==a[it]-'0');
		it++;
	}
	cout<<res<<"\n";
}

int main()
{
	cin.tie(0); ios_base::sync_with_stdio(0);
	cin>>a>>b;
	while(a.size()<b.size())
		a='0'+a;
	solve();
	return 0;
}
