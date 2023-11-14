struct Node
{
    int vertex;
    int weight;
    struct Node *nextNode;
} Node;

struct Graph
{
    int noOfVertices;
    struct Node **adjacencyLists;
    char *description;
} Graph;

struct Vector
{
    void *data;
    int size;
    int currentNumberOfElements;
} Vector;

