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
void RadiusDiameter(int **, int *, int, int);
void Vertices(int **, int, int, int);

int size;   //Размер графа


int main()
{
    int i, j, v;
    int **graph = NULL, *DIST = NULL, **graphO = NULL, *DISTO = NULL;


    printf("\t# Graphs #\n\n < Undirected graph >\n");
    printf("Enter the number of graph vertices (positive integer): ");
    scanf("%d", &size);

    // Creating the graph
    graph = Creategraph(graph, size);
    DIST = (int *)(malloc(sizeof(int *) * size));  // Array for visited vertices
    DISTO = (int *)(malloc(sizeof(int *) * size));

    // Printing the matrix
    for(i = 0; i < size; i++)
    {
        DIST[i] = -1;
        DISTO[i] = -1;
       // visited[i] = 0;
        for(j = 0; j < size; j++)
            printf("%3d ", graph[i][j]);
        printf("\n");
    }

    int num = size - 1;

    printf("Enter the number of start vertex (positive integer [0; %d]): ", num);
    scanf("%d", &v);

    // <---------- ! ---------->
    BFSD(graph, DIST, size, v);
    // <---------- ! ---------->
    //printf("\n");
    for(i = 0; i < size; i++)
        printf("%d: %d\n", i, DIST[i]);

    RadiusDiameter(graph, DIST, size, 0);

    printf("\n\n < Directed graph >\n");

    printf("Enter the number of graph vertices (positive integer): ");
    scanf("%d", &size);
    graphO = CreategraphO(graphO, size);

    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
            printf("%3d ", graphO[i][j]);
        printf("\n");
    }

    //for(i = 0; i < size; i++)
        //visited[i] = 0;

    printf("Enter the number of start vertex (positive integer [0; %d]): ", num);
    scanf("%d", &v);

    // <---------- ! ---------->
    BFSD(graphO, DISTO, size, v);
    // <---------- ! ---------->
    //printf("\n");
    for(i = 0; i < size; i++)
        printf("%d: %d\n", i, DISTO[i]);

    RadiusDiameter(graphO, DISTO, size, 0);


    delete[] DISTO;
    delete[] graphO;
    //delete[] visited;
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
        //printf("%d ", v);
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

void RadiusDiameter(int **graph, int *DIST, int size, int v)
{
    int i, j, temp;
    int *arr;
    arr = (int *)(malloc(sizeof(int *) * size));

    for(i = 0; i < size; i++)
        DIST[i] = -1;

    for(i = 0; i < size; i++)
    {
        BFSD(graph, DIST, size, i);

        for(j = 0; j < size; j++)
            printf("%d ", DIST[j]);
        printf("  ");

        // __________ Сортировка пузырьком __________
        for (int k = 0; k < size - 1; k++)
        {
            for (int n = 0; n < size - k - 1; n++) {
                if (DIST[n] > DIST[n + 1]) {
                    // меняем элементы местами
                    temp = DIST[n];
                    DIST[n] = DIST[n + 1];
                    DIST[n + 1] = temp;
                }
            }
        }
        // __________________________________________

        arr[i] = DIST[size - 1];

        for(j = 0; j < size; j++)
            DIST[j] = -1;
        //printf("  ");

    }

       // __________ Сортировка пузырьком __________
        for (int k = 0; k < size - 1; k++)
        {
            for (int n = 0; n < size - k - 1; n++) {
                if (arr[n] > arr[n + 1]) {
                    // меняем элементы местами
                    temp = arr[n];
                    arr[n] = arr[n + 1];
                    arr[n + 1] = temp;
                }
            }
        }
        // __________________________________________

    printf("\n");
    for(i = 0; i < size; i++)
        printf("%d ", arr[i]);

    printf("\nRadius = %d\nDiametr = %d\n", arr[0], arr[size - 1]);

    Vertices(graph, size, arr[0], arr[size - 1]);

    delete[] arr;
}

void Vertices(int **graph, int size, int radius, int diameter)
{
    int i, j, temp;
    int *DIST;
    DIST = (int *)(malloc(sizeof(int *) * size));

    for(i = 0; i < size; i++)
        DIST[i] = -1;

    for(i = 0; i < size; i++)
    {
        BFSD(graph, DIST, size, i);

        // __________ Сортировка пузырьком __________
        for (int k = 0; k < size - 1; k++)
        {
            for (int n = 0; n < size - k - 1; n++) {
                if (DIST[n] > DIST[n + 1]) {
                    // меняем элементы местам
                    temp = DIST[n];
                    DIST[n] = DIST[n + 1];
                    DIST[n + 1] = temp;
                }
            }
        }
        // __________________________________________


        if(DIST[size - 1] == radius) printf("%d - Central vertex\n", i);
        else if(DIST[size - 1] == diameter) printf("%d - Peripheral vertex\n", i);

        for(j = 0; j < size; j++)
            DIST[j] = -1;
    }

    delete[] DIST;
}
