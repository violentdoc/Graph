#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 	2000

char vis[N + 1];

struct info {
	int *a;
	int c;
} edge[N + 1];

void rlc (struct info *edge, int i, int c) {
	edge[i].a = (int *) realloc (edge[i].a, c * sizeof *edge[i].a);
}

void push (struct info *edge, int u, int v) {
	int c; 
	c = edge[u].c += 1;

	rlc (edge, u, c);

	edge[u].a[c - 1] = v;
}

int dfs (struct info *edge, int node, int parent) {
	int i, ai;
	vis[node] = 0;
	
	for (i = 0; i < edge[node].c ; i++) {
		ai = edge[node].a[i];
		if ( vis[ai] == 0) {
			if (ai != parent) {
				return 1;
			}
		}
		else {
			return dfs (edge, ai, node);
		}
	}
	return 0;
}

int main () {
	int n, e, u, v, i, cycle;
	scanf("%d%d", &n, &e);

	while (e--) {
		scanf("%d%d", &u, &v);
		push (edge, u, v);
		push (edge, v, u);
	}

	memset (vis, 1, sizeof vis);

	cycle = dfs (edge, 1, -1);

	puts (cycle ? "YES it contains a cycle" : "NO it doesn't contain any cycle");

	return 0;
}