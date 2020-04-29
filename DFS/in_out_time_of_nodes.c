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
		//we are not passing &t because	
		//it is already converted into an address of the original variable t
		dfs(edge, edge[node].a[i], t);
	}

	out[node] = (*t)++;
}

int main () {
	int n, e, u, v, i, t;
	scanf("%d%d", &n, &e);

	while (e--) {
		scanf("%d%d", &u, &v);
		push (edge, u, v);
		push (edge, v, u);
	}

	memset (vis, 1, sizeof vis);
	
	t = 1;
	dfs(edge, 1, &t);

	printf("num - intime - outtime\n");
	for (i = 1; i <= n; i++) {
		printf("%d\t%d\t%d\n", i, in[i], out[i]);
	}

	

	return 0;
}