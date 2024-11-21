#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <map>

using namespace std;

int** create_adjacency_matrix(int v);
int cout_matrix(int** G, int v);
void BFS_matrix(int** g, int v, int size, bool* vis, int* d);

void main()
{
	int size = 0, to_start_with;
	cout << "input graph size: ";
	cin >> size;
	int** M = create_adjacency_matrix(size);
	cout_matrix(M, size);
	cout << endl;

	bool* visited = new bool[size];
	int* depth = new int[size];
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
	queue<int> q;
	q.push(v);
	vis[v] = true;
	d[v] = 0;

	map<int, vector<int>> depth_map;

	while (!q.empty())
	{
		v = q.front();
		q.pop();
		depth_map[d[v]].push_back(v);

		for (int i = 0; i < size; i++)
		{
			if (g[v][i] == 1 && !vis[i])
			{
				d[i] = d[v] + 1;
				vis[i] = true;
				q.push(i);
			}
		}
	}

	cout << endl << "Vertices grouped by depth:" << endl;
	for (const auto& depth_pair : depth_map)
	{
		int depth = depth_pair.first;
		const vector<int>& vertices = depth_pair.second;

		cout << "Depth " << depth << ": ";
		for (int vertex : vertices)
		{
			cout << vertex << " ";
		}
		cout << endl;
	}
}