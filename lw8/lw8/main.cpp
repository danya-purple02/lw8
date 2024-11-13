#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

int** create_adjacency_matrix(int v);
int cout_matrix(int** G, int v);

void main() 
{
	int vertexes = 0;
	cout << "input graph size: ";
	cin >> vertexes;
	int** M = create_adjacency_matrix(vertexes);
	cout_matrix(M, vertexes);
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

int cout_matrix(int** G, int v)
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
			cout << G[i][j] << " ";
		}
		cout << endl;
	}
	return 1;
}