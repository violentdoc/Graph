#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N	100000

char visited[N + 1];

struct info{
	int *a;
	int c = 0;
} edge[N + 1];

int traverse(int u, int v){
	for(int i = 0; i < edge[u].c; i++){
		if(edge[u].a[i] == v){
			return i;
		}
	}
	return -1;
}

void rlc(int u, int v, int c1, int c2){
	edge[u].a = (int *) realloc(edge[u].a, c1 * sizeof(*edge[u].a));
	edge[v].a = (int *) realloc(edge[v].a, c2 * sizeof(*edge[v].a));
}

void push(int u, int v){
	int ind = traverse(u, v);
	int c1, c2;
	if(ind == -1){
		c1 = edge[u].c += 1;
		c2 = edge[v].c += 1;

		rlc(u, v, c1, c2);

		edge[u].a[c1 - 1] = v;
		edge[v].a[c2 - 1] = u; 
	}
}

void dfs(struct info edge[], int n, int node){
	if(visited[node] == 0){
		return;
	}
	visited[node] = 0;

	printf("%d\n", node);

	for(int i = 0; i < edge[node].c; i++){
		dfs(edge, n, edge[node].a[i]);
	}
}

int main(){

	int n, m, u, v, root;

	printf("Enter the number of nodes & the number of edges\n");
	scanf("%d%d", &n, &m);

	while(m--){
		scanf("%d%d", &u, &v);
		push(u, v);
	}

	memset(visited, 1, sizeof(visited));


	printf("Enter the root node\n");
	scanf("%d", &root);
	dfs(edge, n, root);


	return 0;
}