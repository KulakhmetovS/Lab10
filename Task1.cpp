#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>


using namespace std;

int** Creategraph(int **, int); //Создание графа
int** CreategraphO(int **, int); //Создание ориентированного графа
void BFSD(int **, int *, int, int);  //Обход в ширину

int size;   //Размер графа


int main()
{
    int i, j, v;
    int **graph = NULL, *DIST = NULL, *visited = NULL, **graphO = NULL, *DISTO = NULL;


    printf("\t# Graphs #\n\n");
    printf("Enter the number of graph vertices (positive integer): ");
    scanf("%d", &size);

    // Creating the graph
    graph = Creategraph(graph, size);
    DIST = (int *)(malloc(sizeof(int *) * size));  // Array for visited vertices
    DISTO = (int *)(malloc(sizeof(int *) * size));
    visited = (int *)(malloc(sizeof(int *) * size));

    // Printing the matrix
    for(i = 0; i < size; i++)
    {
        DIST[i] = -1;
        DISTO[i] = -1;
        visited[i] = 0;
        for(j = 0; j < size; j++)
            printf("%3d ", graph[i][j]);
        printf("\n");
    }

    int num = size - 1;

    printf("Enter the number of start vertex (positive integer [0; %d]): ", num);
    scanf("%d", &v);
    printf("\t# BFS distance #\n");

    // <---------- ! ---------->
    BFSD(graph, DIST, size, v);
    // <---------- ! ---------->
    printf("\n");
    for(i = 0; i < size; i++)
        printf("%d: %d\n", i, DIST[i]);
    printf("\n\n");

    printf("Enter the number of graph vertices (positive integer): ");
    scanf("%d", &size);
    graphO = CreategraphO(graphO, size);

    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
            printf("%3d ", graphO[i][j]);
        printf("\n");
    }

    for(i = 0; i < size; i++)
        visited[i] = 0;

    printf("Enter the number of start vertex (positive integer [0; %d]): ", num);
    scanf("%d", &v);
    printf("\t# BFS distance #\n");

    // <---------- ! ---------->
    BFSD(graphO, DISTO, size, v);
    // <---------- ! ---------->
    printf("\n");
    for(i = 0; i < size; i++)
        printf("%d: %d\n", i, DISTO[i]);


    delete[] DISTO;
    delete[] graphO;
    delete[] visited;
    delete[] graph;
    delete[] DIST;

    return 0;
}


int** Creategraph(int **graph, int size)
{
    srand(time(NULL));

    int i = 0, j = 0;

    // Memory allocation
    graph = (int **)(malloc(sizeof(int *) * size));
    for(i = 0; i < size; i++)
        graph[i] = (int *)(malloc(sizeof(int *) * size));

    // Filling the matrix
    for(i = 0; i < size; i++)
        for(j = i; j < size; j++)
        {
            graph[i][j] = rand() % 4;
            graph[j][i] = graph[i][j];
            if(i == j) graph[i][j] = 0;
            //if(graph[i][j] == 1);
        }

    return graph;
}

void BFSD(int **graph, int *DIST, int size, int v)
{
    queue<int> q;
    q.push(v);
    DIST[v] = 0;

    while(!q.empty())
    {
        v = q.front();
        printf("%d ", v);
        q.pop();

        for(int i = 0; i < size; i++)
        {
            if((graph[v][i] > 0) && (DIST[i] == -1))
            {
                q.push(i);
                DIST[i] = DIST[v] + graph[v][i];
            }
        }
    }

}

int** CreategraphO(int **graph, int size)
{
    srand(time(NULL));

    int i = 0, j = 0;

    // Memory allocation
    graph = (int **)(malloc(sizeof(int *) * size));
    for(i = 0; i < size; i++)
        graph[i] = (int *)(malloc(sizeof(int *) * size));

    // Filling the matrix
    for(i = 0; i < size; i++)
        for(j = 0; j < size; j++)
        {
            graph[i][j] = rand() % 4;
            //graph[j][i] = graph[i][j];
            if(i == j) graph[i][j] = 0;
            //if(graph[i][j] == 1);
        }

    return graph;
}
