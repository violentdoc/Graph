#include <stdio.h>

#define N 	2000

int oo[1 + (N - 1) * 2], oj[1 + (N - 1) * 2];

int link (int o, int j) {
	static int _ = 1;

	oo[_] = o, oj[_] = j;
	return _++;
}

int ae[N];

void dfs (int p, int i) {
	int o, j;
	printf("%d ", i + 1);
	for (o = ae[i]; o; o = oo[o]) {
		j = oj[o];
		if (j != p) {
			dfs (i, j);
		}
	}
}

int main () {
	int n, e, i, j, h, d;
	printf("enter the number of nodes and edges\n");
	scanf("%d%d", &n, &e);
	
	for (h = 0; h < e; h++) {
		scanf("%d%d", &i, &j);
		i--, j--;
		ae[i] = link (ae[i], j);
		ae[j] = link (ae[j], i);
	}

	printf("enter the node you want to travel from\n");
	scanf("%d", &d);
	d--;
	
	dfs (-1, d);
}