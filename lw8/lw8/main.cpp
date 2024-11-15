#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <time.h>

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
void BFS_matrix_Queue(int** g, int v, int size, bool* vis, int* d);
void BFS_matrix_q(int** g, int v, int size, bool* vis, int* d);

struct Queue* make_struct(int data);
int pop_q();
void push_q(int v);

struct Queue* head = NULL, * last = NULL, * f = NULL, * tmp = NULL;

void main() 
{
	clock_t start = 0, end = 0, res_q = 0, res_Queue = 0;
	int size, to_start_with;

	cout << "input input number of vertex to start Broad-first search with: ";
	cin >> to_start_with;

	for (size = 1000; size <= 10000; size = size + 1000) 
	{
		int** M = create_adjacency_matrix(size);
		//cout_matrix(M, size);
		//cout << endl;

		bool *visited = new bool[size];
		int *depth = new int[size];
		for (int i = 0; i < size; i++) 
		{
			visited[i] = 0;
			depth[i] = 0;
		}
	
		//cout << "Breadth-first search using c++ class queue: " << endl;

		start = clock();
		while (!visited[to_start_with])
		{
			BFS_matrix_q(M, to_start_with, size, visited, depth);
		}
		end = clock();
		res_q = end - start;
		//cout << endl << "---------------------------------" << endl;
	
		start = 0, end = 0;
		for (int i = 0; i < size; i++)
		{
			visited[i] = 0;
			depth[i] = 0;
		}
		//cout << "Breadth-first search using self-made Queue struct: " << endl;
		start = clock();
		while (!visited[to_start_with])
		{
			BFS_matrix_Queue(M, to_start_with, size, visited, depth);
		}
		end = clock();
		res_Queue = end - start;
		cout << "---------------------------------" << endl;

		cout << "matrix size: " << size << endl;
		cout << "time spent with using c++ class queue: " << res_q / 10000.0 << endl;
		cout << "time spent with using self-made Queue struct: " << res_Queue / 10000.0 << endl;
		delete[] M;
		delete[] visited;
		delete[] depth;
	}
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

void BFS_matrix_Queue(int** g, int v, int size, bool* vis, int* d)
{
	struct Queue* q = NULL;
	push_q(v);
	vis[v] = 1;
	d[v] = 0;

	while (!head == NULL) 
	{
		v = head->inf;
		pop_q();
		//cout << v << " -> ";
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

void BFS_matrix_q(int** g, int v, int size, bool* vis, int* d)
{
	queue<int> q;
	q.push(v);
	vis[v] = 1;
	d[v] = 0;

	while (!q.empty())
	{
		v = q.front();
		q.pop();
		//cout << v << " -> ";
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