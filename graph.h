#include<stdio.h>

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int noOfVertices;
    struct Node** adjacencyLists;
};

struct Graph initGraph(int noOfVertices, char** matrixRows);