// Simulation of bfs and dfs on hardcoded tree
// functions of bfs and dfs can be used independently
// Tip: this code is good to use for exams
// Credits: RN

#include<iostream>
#include<conio.h>
using namespace std;

int visited[7], n;
int front = 0;
int rear = 0;
int que[7] = { 0 };

//if an edge exists then inser 1 else 0
int arr[7][7] =
{	//0 1  2  3  4  5  6	
	{ 0, 1, 0, 0, 0, 0, 0 }, //0
	{ 0, 0, 1, 0, 1, 0, 1 }, //1
	{ 0, 0, 0, 1, 0, 1, 0 }, //2
	{ 0, 0, 0, 0, 0, 0, 0 }, //3
	{ 0, 0, 0, 0, 0, 0, 0 }, //4
	{ 0, 0, 0, 0, 0, 0, 0 }, //5
	{ 0, 0, 0, 0, 0, 0, 0 }, //6
};

//breadth First Search
void bfs(int v)
{
	visited[v] = 1;
	que[rear] = v;
	rear++;
	while (rear != front)
	{
		int u = que[front];
		cout << u <<" ";
		front++;
		for (int i = 0; i < 7; i++)
		{
			if (!visited[i] && arr[u][i])
			{
				que[rear] = i;
				rear++;
				visited[i] = 1;
			}
		}
	}
	cout << endl;
}

//depth first search
void dfs(int i)
{
	int j;
	cout << i <<" ";
	visited[i] = 1;

	for (j = 0; j<7; j++)
		if (!visited[j] && arr[i][j] == 1)
			dfs(j);
}

void main()
{
	int start;
	for (int i = 0; i < 7; i++)
	{
		visited[i] = 0;
	}

	cout << "\n\t\t\tBFS & DFS\n\n  Start traversal at node: ";
	cin >> start;
	cout << "\n  BFS: ";
	bfs(start);
	for (int i = 0; i < 7; i++)
	{
		visited[i] = 0;
	}
	cout << "\n  DFS: ";
	dfs(start);
	_getch();
}