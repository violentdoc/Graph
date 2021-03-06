#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N	10000

char visited[N + 1];
int dis[N + 1];

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

void rlc(struct info *edge, int u, int c1){
	edge[u].a = (int *) realloc(edge[u].a, c1 * sizeof(*edge[u].a));
}

void push(int u, int v){
	int ind = traverse(u, v);
	int c1, c2;
	
	if(ind == -1){
		c1 = edge[u].c += 1;
		c2 = edge[v].c += 1;
		
		rlc(edge, u, c1);
		rlc(edge, v, c2);
		
		edge[u].a[c1 - 1] = v;
		edge[v].a[c2 - 1] = u;
	}
}

void dfs(struct info *edge, int node, int d){
	int i, t;
	
	if(visited[node] == 0){
		return;
	}
	visited[node] = 0;
	
	t = dis[node];
	if( (d != 0 && t > d) || dis[node] == 0){
		dis[node] = d;
	}

	for(i = 0; i < edge[node].c; i++){
		dfs(edge, edge[node].a[i], d + 1);
	}


}

int main(){


	int n, e, u, v, i, dd;

	printf("enter the number of nodes and the number of edges\n");
	scanf("%d%d", &n, &e);

	while(e--){
		scanf("%d%d", &u, &v);
		push(u, v);
	}

	memset(visited, 1, sizeof(visited));
	memset(dis, 0, sizeof(dis));

	printf("distances should be counted from what node\n");
	scanf("%d", &dd);

	dfs(edge, dd, 0);

	printf("distance of all the nodes from %d\n", dd);
	for(int i = 1; i <= n; i++){
		printf("%d ", dis[i]);
	}
	
	//related problem : https://www.hackerearth.com/practice/algorithms/graphs/depth-first-search/practice-problems/algorithm/bishu-and-his-girlfriend/


	return 0;
}
