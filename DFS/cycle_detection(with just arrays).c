#include <stdio.h>

#define N 	2000

int oo[1 + N * 2], oj[1 + N * 2];

int link (int o, int j) {
	static int _ = 1;

	oo[_]= o, oj[_] = j;
	return _++;
}

int ae[N], vis[N];

int dfs (int p, int i) {
	int o, j;
	vis[i] = 1;

	for (o = ae[i]; o; o = oo[o]) {
		j = oj[o];
		if (vis[j]) {
			if (j != p) {
				return 1;
			}
		}
		else return dfs (i, j);
	}
}

int main () {
	int n, e, i, j, h, cycle;
	scanf("%d%d", &n, &e);

	for (h = 0; h < e; h++) {
		scanf("%d%d", &i, &j), i--, j--;
		ae[i] = link (ae[i], j);
		ae[j] = link (ae[j], i);
	}

	cycle = 0;
	cycle = dfs (-1, 2);

	puts (cycle ? "YES there's a cycle in between" : "NO there isn't");
}