#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N	10000

char visited[N + 1];

struct info{
	int *a;
	int c = 0;
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

void dfs(struct info *edge, int node){
	int i;
	
	if(visited[node] == 0){
		return;
	}
	visited[node] = 0;
	
	for(i = 0; i < edge[node].c; i++){
		dfs(edge, edge[node].a[i]);
	}
}

int main(){


	int n, e, u, v, cnt = 0, i;

	printf("enter the the number of nodes and the number edges\n");
	scanf("%d%d", &n, &e);

	while(e--){
		scanf("%d%d", &u, &v);
		push(u, v);
	}

	memset(visited, 1, sizeof(visited));


	for(i = 1; i <= n; i++){
		if(visited[i] == 1){
			++cnt;
		}
		dfs(edge, i);
	}

	printf("there are %d connected components\n", cnt);
	
	//related problem link : 1. https://www.hackerearth.com/problem/algorithm/connected-components-in-a-graph/
	// 2. https://www.spoj.com/problems/PT07Y/




	return 0;
}
