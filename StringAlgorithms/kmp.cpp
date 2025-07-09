// Task : CSES Finding Borders
// AC : https://cses.fi/problemset/result/11663600/
 
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
vector<int> kmp;
stack<int> st;

int main()
{
	cin.tie(0); ios_base::sync_with_stdio(0);
	cin>>s;
	n=s.size();
	kmp.resize(n);
	for(int i=1,j=0;i<n;i++)
	{
		while(j && s[i]!=s[j])
			j=kmp[j-1];
		j+=(s[i]==s[j]);
		kmp[i]=j;
	}
	int it = n-1;
	while(kmp[it])
	{
		st.push(kmp[it]);
		it=kmp[it]-1;
	}
	while(st.size())
	{
		cout<<st.top()<<" ";
		st.pop();
	}
	return 0;
}
