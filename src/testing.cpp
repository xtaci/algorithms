#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void r()
{
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
#endif
}

int main()
{	r();

	int n;
	cin >> n;
	vector<pair<ll, ll>>M
	                  for (int i = 0; i < n; i++)
	{
		ll a, b;
		cin >> a >> b;
		M.push_back({a, b});
	}
	ans = -1;
	sort(M.begin(), M.end())

	for (auto i : M)
	{
		if (ans > i.second)
		{
			ans = i.first ;
		}
		else
		{
			ans = i.second;
		}
	}
	cout << ans;



	return 0;
}
