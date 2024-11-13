#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>

using namespace std;

struct Node
{
	int vertex;
	struct Node* next;
};

struct Graph
{
	int vertexes_amount;
	struct Node** list;
};

int** create_adjacency_matrix(int v);
int cout_matrix(int** G, int v);
void BFS_matrix(int** g, int v, int size, bool* vis, int* d);

struct Graph* create_adjacency_list(int vertexes);
struct Node* create_vertex(int vertex);
void connect_vertexes(struct Graph* graph, int coll, int dest);
void cout_adjacency_list(struct Graph* graph);
void BFS_list(struct Graph* G, int start, int size, bool* vis, int* d);

void main() 
{
	int size = 0, to_start_with;
	cout << "input graph size: ";
	cin >> size;
	int** M = create_adjacency_matrix(size);
	cout_matrix(M, size);
	cout << endl;

	bool *visited = new bool[size];
	int *depth = new int[size];
	for (int i = 0; i < size; i++) 
	{
		visited[i] = 0;
		depth[i] = 0;
	}
	cout << "input input number of vertex to star with: ";
	cin >> to_start_with;
	cout << endl;
	cout << "Breadth-first matrix search: " << endl;
	while (!visited[to_start_with])
	{
		BFS_matrix(M, to_start_with, size, visited, depth);
	}
	cout << endl << "---------------------------------" << endl;

	struct Graph* G1 = create_adjacency_list(size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (M[i][j] == 1)
			{
				connect_vertexes(G1, i, j);
			}
		}
	}
	cout_adjacency_list(G1);
	cout << endl;

	for (int i = 0; i < size; i++)
	{
		visited[i] = 0;
		depth[i] = 0;
	}
	to_start_with = 0;
	cout << "input input number of vertex to star with: ";
	cin >> to_start_with;
	cout << endl;
	cout << "Breadth-first matrix search: " << endl;
	BFS_list(G1, to_start_with, size, visited, depth);
	return;
}

int** create_adjacency_matrix(int v)
{
	srand(time(NULL));
	int** G = new int* [v];

	for (int i = 0; i < v; i++)
	{
		G[i] = new int[v];
	}

	for (int i = 0; i < v; i++)
	{
		for (int j = 0; j < v; j++)
		{
			if (j < i)
			{
				G[i][j] = G[j][i];
			}
			else
			{
				G[i][j] = rand() % 2;
			}
		}
	}

	return G;
}

int cout_matrix(int** g, int v)
{
	cout << "    ";
	for (int i = 0; i < v; i++)
	{
		cout << i << " ";
	}
	cout << endl << endl;
	for (int i = 0; i < v; i++)
	{
		cout << i << "   ";
		for (int j = 0; j < v; j++)
		{
			cout << g[i][j] << " ";
		}
		cout << endl;
	}
	return 1;
}

void BFS_matrix(int** g, int v, int size, bool* vis, int* d)
{
	queue<int> q;
	q.push(v);
	vis[v] = 1;
	d[v] = 0;

	while (!q.empty()) 
	{
		v = q.front();
		q.pop();
		cout << v << " -> ";
		for (int i = 0; i < size; i++)
		{
			if (g[v][i] == 1 && !vis[i]) 
			{
				d[i] = d[v] + 1;
				vis[i] = 1;
				q.push(i);
			}
		}
	}
}

struct Graph* create_adjacency_list(int vertexes)
{
	struct Graph* graph = new struct Graph;
	graph->vertexes_amount = vertexes;
	graph->list = new struct Node* [vertexes];
	for (int i = 0; i < vertexes; i++)
	{
		graph->list[i] = new struct Node[vertexes];
	}

	for (int i = 0; i < vertexes; i++)
	{
		graph->list[i] = create_vertex(i);
	}

	return graph;
}

struct Node* create_vertex(int vertex)
{
	struct Node* new_node = new struct Node;
	new_node->vertex = vertex;
	new_node->next = NULL;
	return new_node;
}

void connect_vertexes(struct Graph* graph, int coll, int dest)
{
	struct Node* new_node = create_vertex(dest);
	int i = 0;
	while (graph->list[i]->vertex != coll)
	{
		i++;
	}

	struct Node* tmp = graph->list[i];
	while (tmp->next != NULL)
	{

		tmp = tmp->next;
	}

	tmp->next = new_node;
}

void cout_adjacency_list(struct Graph* graph)
{
	cout << endl << "adjacency list:" << endl;
	struct Node* tmp;
	for (int i = 0; i < graph->vertexes_amount; i++)
	{
		tmp = graph->list[i];
		while (tmp)
		{
			cout << tmp->vertex;
			tmp = tmp->next;
			if (tmp != NULL)
			{
				cout << " -> ";
			}
		}
		cout << endl;
	}
}

void BFS_list(struct Graph* G, int start, int size, bool* vis, int* d)
{
	std::queue<int> q;
	q.push(start);
	vis[start] = true;
	d[start] = 0;

	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		cout << v << " -> ";

		struct Node* l = G->list[v];
		while (l != NULL)
		{
			v = l->vertex;
			if (!vis[v])
			{
				q.push(v);
				vis[v] = true;
				d[v] = d[v] + 1;
			}
			l = l->next;
		}
	}
}
