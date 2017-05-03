#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

const int N = 205;
int n, f[N][N], tot[N*N];
pair<int, int> fac[N*N][15]/*15试出来的，否则MLE*/;

int search(int a, int b, int dep)
{//搜索j，k是否要i次才能猜出来
	int s = a + b, p = a*b, i, flag = 1;
	if (dep % 2 == 0) {
		for (i = 1; i + i<s; i++)
			if (i != a && s - i <= n && f[i][s - i] >= dep) {
				flag = 0; break;
			}
		if (flag) f[a][b] = dep;
	}
	else {
		for (i = 1; i <= tot[p]; i++)
			if (fac[p][i].first != a && f[fac[p][i].first][fac[p][i].second] >= dep) {
				flag = 0; break;
			}
		if (flag) f[a][b] = dep;
	}
	return f[a][b] == dep;
}

void preset()
{
	for (int i = 1; i<n; i++)
		for (int j = i + 1; j <= n; j++) {
			tot[i*j]++;
			fac[i*j][tot[i*j]] = make_pair(i, j);
		}
}

int main()
{
	int i, j, k, m, ans = 0;
	cin >> n >> m;
	memset(f, 0x3f, sizeof(f));
	preset();
	for (i = 0; i <= m; i++) {
		int flag = 0;
		for (j = 1; j <= n; j++)
			for (k = j + 1; k <= n; k++)
				if (f[j][k]>m)
					flag |= search(j, k, i);
		if (!flag) break;
	}
	for (i = 1; i <= n; i++)
		for (j = i + 1; j <= n; j++)
			if (f[i][j] == m) ans++;
	printf("%d\n", ans);
	for (i = 1; i <= n; i++)
		for (j = i + 1; j <= n; j++)
			if (f[i][j] == m) printf("%d %d\n", i, j);
	system("pause");
	return 0;
}