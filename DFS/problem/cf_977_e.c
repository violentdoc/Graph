/* https://codeforces.com/contest/977/submission/37947050 (L0oSeR) */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N	200000

char visited[N + 1];
int com[N + 1];

struct info{
	int *a;
	int c;
} edge[N + 1], comp[N + 1];


void rlc(struct info *edge, int u, int c){
	edge[u].a = (int *) realloc(edge[u].a, c * sizeof *edge[u].a);
}

void push(struct info *edge, int u, int v){
	int c;
	
	c = edge[u].c += 1;

	rlc(edge, u, c); 

	edge[u].a[c - 1] = v;
}

//this dfs also making sure that,
//kon koto number connected component a ase, shetaw save koretese "com" array te
void dfs(struct info *edge, int node, int cnt){
	int i;
	if(visited[node] == 0){
		return;
	}
	visited[node] = 0;
	com[node] = cnt;

	for(i = 0; i < edge[node].c; i++){
		dfs(edge, edge[node].a[i], cnt);
	}
}

int main(){

	int n, e, u, v, i, j, cnt, ans, f;
	scanf("%d%d", &n, &e);

	while(e--){
		scanf("%d%d", &u, &v);
		push(edge, u, v);
		push(edge, v, u);
	}

	memset(visited, 1, sizeof(visited));

	cnt = 0;
	for(i = 1; i <= n; i++){
		if(visited[i] == 1){
			++cnt;
			dfs(edge, i, cnt);
		}
	}

	//prottek connted component er ekta array thakbe and array te,
	//jegulu shei component er shathe connected shegulu saved thakbe
	for(i = 1; i <= n; i++){
		push(comp, com[i], i);
	}

	ans = 0;
	for(i = 1; i <= cnt; i++){
		f = 1;
		//prottek connected components er array te,
		//shob elements er haat or edge exactly duita thaklei ekta perfect loop pawa jabe
		for(j = 0; j < comp[i].c; j++){
			if(edge[comp[i].a[j]].c != 2){
				f = 0;
				break;
			}
		}
		ans += f;
	}

	printf("%d\n", ans);

	return 0;
}