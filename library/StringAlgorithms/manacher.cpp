// Task : Longest Palindrome 
// AC : https://cses.fi/problemset/result/11664007/
 
#include <bits/stdc++.h>
#define pb push_back
#define ll long long 
#define gc getchar_unlocked
using namespace std;
//-------------------------code-------------------------//
const int MAXN = 1e6+3;
const ll INF = 1e9+97; 

int n;
string s;
vector<int> p[2];
int a=0, b=0;

int main()
{
	cin.tie(0); ios_base::sync_with_stdio(0);
	cin>>s;
	s='$'+s+'^';
	n=s.size();
	for(int j=0;j<2;j++)
	{
		p[j].resize(n);
		for(int i=1,l=1,r=1;i<n;i++)
		{
			p[j][i]=max(0, min(r-i, p[j][l+r-i]));
			while(s[i+p[j][i]+j]==s[i-p[j][i]])
				p[j][i]++;
			if(i+p[j][i]>r)
			{
				r=i+p[j][i];
				l=i-p[j][i];
			}
			if(b-a+1<r-l+1+j)
			{
				a=l;
				b=r+j;
			}
		}
	}
	for(int i=a+1;i<b;i++)
		cout<<s[i];
	return 0;
}
