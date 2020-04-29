#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 	2000

char vis[N + 1];
int in[N + 1];
int out[N + 1];

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

void dfs (struct info *edge, int node, int *t) {
	int i;
	if (vis[node] == 0) {
		return;	
	}
	vis[node] = 0;
	in[node] = (*t)++;

	for (i = 0; i < edge[node].c ; i++) {
		dfs(edge, edge[node].a[i], t);
	}

	out[node] = (*t)++;
}

int main () {
	int n, e, q, u, v, x, y, i, t;
	
	printf("enter the number nodes, edges and the number of queries\n");
	scanf("%d%d%d", &n, &e, &q);

	while (e--) {
		scanf("%d%d", &u, &v);
		push (edge, u, v);
		push (edge, v, u);
	}

	memset (vis, 1, sizeof vis);
	
	t = 1;
	dfs(edge, 1, &t);

	while (q--) {
		scanf("%d%d", &x, &y);
		printf( in[x] > in[y] && out[x] < out[y] ? "YES %d is a subtree / sub child of %d\n" : "NO %d is not a subtree / sub child of %d\n", x, y);
	}

	

	return 0;
}