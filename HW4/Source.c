#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define MAX 50

int all, n, graph[MAX][MAX];
struct Graph* g;

void init() {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			graph[i][j] = -1;
		}
	}
}

void readGraph(){
	scanf("%d", &n);
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < n; c++) {
			scanf("%d", &graph[r][c]);
		}
	}
}

void process() {
	init();
	readGraph();
}

struct AjlistNode{
	int id;
	struct AjlistNode* next;
};
struct Vertices{
	int data;
	struct AjlistNode* next;
	struct AjlistNode* end;
};
struct Graph{
	struct Vertices* node;
};
void setData(struct Graph* g){
	if (g->node != NULL){
		int index = 0;
		for (int index = 0; index < n; index++) {
			g->node[index].data = index;
			g->node[index].next = NULL;
			g->node[index].end = NULL;
		}
	}
}

struct Graph* newGraph()
{
	struct Graph* g = (struct Graph*)
		malloc(sizeof(struct Graph));
	g->node = (struct Vertices*)malloc(sizeof(struct Vertices) * n);
	setData(g);
	return g;
}
void connect(struct Graph* g, int start, int end){
	struct AjlistNode* edge = (struct AjlistNode*)
		malloc(sizeof(struct AjlistNode));
	if (edge != NULL){
		edge->id = end;
		edge->next = NULL;
		if (g->node[start].next == NULL){
			g->node[start].next = edge;
		}
		else{
			g->node[start].end->next = edge;
		}
		g->node[start].end = edge;
	}
}
void addEdge(struct Graph* g, int start, int end){
	if (start < n && end < n) {
		connect(g, start, end);
	}
}
int detectCycle(struct Graph* g, int start, int point, int visit[]){
	if (visit[start] == 1 && point == start){
		return 1;
	}
	else if (visit[point] == 1){
		return 0;
	}
	visit[point] = 1;
	struct AjlistNode* temp = g->node[point].next;
	int status = 0;
	while (temp != NULL && !status){
		status = detectCycle(g, start, temp->id, visit);
		temp = temp->next;
	}
	return status;
}
int checkCycle(struct Graph* g){
	int visit[MAX];
	int result = 0;
	int location = 0;
	while (location < n && result == 0) {
		for (int index = 0; index < n; index++) {
			visit[index] = 0;
		}
		result = detectCycle(g, location, location, visit);
		location++;
	}
	return result;
}

void loadEdge() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (graph[i][j] == 0) continue;
			addEdge(g, i, j);
		}
	}
}

int main(){
	freopen("C:\\Users\\Dell\\Downloads\\hw4_input.txt", "r", stdin);
	FILE* outFile = fopen("output.txt ", "w");

	scanf("%d\n", &all);

	for (int i = 0; i < all; i++) {
		process();
		g = newGraph(n);
		loadEdge();
		fprintf(outFile,"%d\n", checkCycle(g));
	}

	fclose(outFile);

	return 0;
}
