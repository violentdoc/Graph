#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N	10000

char visited[N + 1];
int col[N + 1];
int ok = 1;

struct info{
	int *a;
	int c;
} edge[N + 1];

int traverse(int u, int v){
	int i;
	for(i = 0; i < edge[u].c; i++){
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

void dfs(struct info *edge, int node, int c){
	int i;

	if(visited[node] == 0){
		if(col[node] != c){
			ok = 0;
		}
		return;
	}
	visited[node] = 0;
	col[node] = c;

	for(i = 0;i < edge[node].c; i++){
		dfs(edge, edge[node].a[i], 1 - c);
	}
}

int main(){

	int n, e, i, u, v;

	printf("enter the number of nodes and the edges\n");
	scanf("%d%d", &n, &e);

	for(i = 0; i < e; i++){
		scanf("%d%d", &u, &v);
		push(u, v);
	}

	memset(visited, 1, sizeof(visited));

	dfs(edge, 1, 1);

	puts( ok ? "Yes it is a Bipartite Graph" : "No it is not a Bipartite Graph");
	
	//realted problem : https://www.spoj.com/problems/BUGLIFE/



	return 0;
}
