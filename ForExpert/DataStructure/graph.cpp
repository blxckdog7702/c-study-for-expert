#include <stdio.h>
#include <malloc.h>

typedef struct adjlistNode
{
	int vertex;
	adjlistNode *next;
} AdjlistNode;

typedef struct
{
	int num_members;
	AdjlistNode *head;
	AdjlistNode *tail;
} AdjList;

typedef struct
{
	int num_vertices;
	AdjList * adjListArr;
} Graph;

AdjlistNode * createNode(int v)
{
	AdjlistNode * newNode = (AdjlistNode *)malloc(sizeof(AdjlistNode));

	newNode->vertex = v;
	newNode->next = NULL;

	return newNode;
}

Graph * createGraph(int n)
{

	Graph * graph = (Graph *)malloc(sizeof(Graph));
	graph->num_vertices = n;

	graph->adjListArr = (AdjList *)malloc(n * sizeof(AdjList));

	for (int i = 0; i < n; i++)
	{
		graph->adjListArr[i].head = graph->adjListArr[i].tail = NULL;
		graph->adjListArr[i].num_members = 0;
	}

	return graph;
}

void destroyGraph(Graph * graph)
{
	if (graph)
	{
		if (graph->adjListArr)
		{
			for (int v = 0; v < graph->num_vertices; v++)
			{
				AdjlistNode * adjListPtr = graph->adjListArr[v].head;
				while (adjListPtr)
				{
					AdjlistNode * tmp = adjListPtr;
					adjListPtr = adjListPtr->next;
					free(tmp);
				}
			}
			free(graph->adjListArr);
		}
		free(graph);
	}
}

void addEdge(Graph *graph, int src, int dest)
{
	AdjlistNode * newNode = createNode(dest);
	if (graph->adjListArr[src].tail != NULL)
	{
		graph->adjListArr[src].tail->next = newNode;
		graph->adjListArr[src].tail = newNode;
	}
	else
	{
		graph->adjListArr[src].head = graph->adjListArr[src].tail = newNode;
	}
	graph->adjListArr[src].num_members++;

	newNode = createNode(src);
	if (graph->adjListArr[dest].tail != NULL)
	{
		graph->adjListArr[dest].tail->next = newNode;
		graph->adjListArr[dest].tail = newNode;
	}
	else
	{
		graph->adjListArr[dest].head = graph->adjListArr[dest].tail = newNode;
	}
	graph->adjListArr[dest].num_members++;
}

void displayGraph(Graph * graph, int i)
{

	AdjlistNode * adjListPtr = graph->adjListArr[i].head;
	while (adjListPtr)
	{
		printf("%d ", adjListPtr->vertex);
		adjListPtr = adjListPtr->next;
	}
	printf("\n");
}

int main(int argc, char* argv[])
{
	int T, V, E, Q, sv, ev;

	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; test_case++)
	{
		scanf("%d %d %d", &V, &E, &Q);

		Graph * graph = createGraph(V);

		for (int i = 0; i < E; i++)
		{
			scanf("%d %d", &sv, &ev);
			addEdge(graph, sv, ev);
		}
		printf("#%d\n", test_case);

		for (int i = 0; i < Q; i++)
		{
			scanf("%d", &sv);
			displayGraph(graph, sv);
		}
	}

	return 0;
}