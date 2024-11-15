#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

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

struct Queue
{
	int inf;
	struct Queue* next;
};

int** create_adjacency_matrix(int v);
int cout_matrix(int** G, int v);
void BFS_matrix(int** g, int v, int size, bool* vis, int* d);

struct Queue* make_struct(int data);
int pop_q();
void push_q(int v);

struct Queue* head = NULL, * last = NULL, * f = NULL, * tmp = NULL;

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
	struct Queue* q = NULL;
	push_q(v);
	vis[v] = 1;
	d[v] = 0;

	while (!head == NULL) 
	{
		v = head->inf;
		pop_q();
		cout << v << " -> ";
		for (int i = 0; i < size; i++)
		{
			if (g[v][i] == 1 && !vis[i]) 
			{
				d[i] = d[v] + 1;
				vis[i] = 1;
				push_q(i);
			}
		}
	}
}

struct Queue* make_struct(int data)
{
	struct Queue* new_str = new struct Queue;
	new_str->inf = data;
	new_str->next = NULL;
	return new_str;
}

void push_q(int data)
{
	struct Queue* p = make_struct(data);
	if (head == NULL && p != NULL)
	{
		head = p;
		last = p;
	}
	else if (head != NULL && p != NULL)
	{
		last->next = p;
		last = p;
	}
}

int pop_q() 
{
	tmp = head->next;
	int data = head->inf;
	delete head;
	head = tmp;
	return data;
}