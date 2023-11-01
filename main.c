#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

struct Node *newNode(int vertex, int weight)
{
    struct Node *node = malloc(sizeof(struct Node));
    node->vertex = vertex;
    node->weight = weight;
    node->nextNode = NULL;
    return node;
}

void printGraph(struct Graph graph)
{

    printf("Amount of vertices: %d\n", graph.noOfVertices);
    printf("Adjacency lists:\n");
    struct Node *temporaryNode = NULL;
    for (int i = 0; i < graph.noOfVertices; i++)
    {
        temporaryNode = graph.adjacencyLists[i];

        printf("%d: ", i);
        while (NULL != temporaryNode)
        {
            printf("(%d, %d) ", temporaryNode->vertex, temporaryNode->weight);
            temporaryNode = temporaryNode->nextNode;
        }

        printf("\n");
    }
    printf("Additional information: %s\n", graph.description);
    printf("-------------------------------------------------\n\n");
}

void printGraphs(struct Graph *graphs, int noOfGraphs)
{

    printf("-------------------------------------------------\n");
    printf("Printing graphs in the following format:\n");

    printf("{vertex}: {(vertex, weight)}\n\n");
    for (int i = 0; i < noOfGraphs; i++)
    {
        printf("------------------Graph %d----------------------\n", i);
        printGraph(graphs[i]);
    }
}
struct Graph *readGraphsFromFile(FILE *filePtr, int *noOfGraphs)
{

    size_t lineLength = 0;
    char *line = NULL;
    char *token = NULL;
    size_t bytesRead = 0;
    int noOfVertices = 0;

    // Read number of graphs in a file
    bytesRead = getline(&line, &lineLength, filePtr);

    if (0 < bytesRead)
    {
        *noOfGraphs = strtol(line, NULL, 10);

#ifdef dbg
        printf("file: %s\n", line);
        printf("Graphs: %d\n", *noOfGraphs);
#endif // dbg
    }

    struct Graph *graphs = malloc(*noOfGraphs * sizeof(Graph));

    for (int i = 0; i < *noOfGraphs; i++)
    {
        bytesRead = getline(&line, &lineLength, filePtr);

        if (0 >= bytesRead)
            continue;

        noOfVertices = strtol(line, NULL, 10);
        graphs[i].noOfVertices = noOfVertices;
#ifdef dbg
        printf("file: %s\n", line);
        printf("Vertices in graph %d: %d \n", i, graphs[i].noOfVertices);
#endif // dbg

        graphs[i].adjacencyLists = malloc(noOfVertices * sizeof(struct Node *));

#ifdef dbg
        printf("New adj matrix[0]: %d\n", graphs[i].adjacencyMatrix[0]);
#endif // dbg
        for (int j = 0; j < noOfVertices; j++)
        {
            graphs[i].adjacencyLists[j] = NULL;
            bytesRead = getline(&line, &lineLength, filePtr);
            if (0 < bytesRead)
            {

                char *ptr = strtok(line, " ");
                int k = 0;
                while (NULL != ptr)
                {
                    int weight = strtol(ptr, NULL, 10);

                    if (weight > 0)
                    {
                        struct Node *node = newNode(k, weight);
                        node->nextNode = graphs[i].adjacencyLists[j];
                        graphs[i].adjacencyLists[j] = node;
                    }

#ifdef dbg
                    printf("file: %s\n", ptr);
                    printf("new vertex in adj list: %d\n", graphs[i].adjacencyMatrix[j * graphs[i].noOfVertices + k]);
#endif // dbg
                    ptr = strtok(NULL, " ");
                    k++;
                }
            }
        }

        bytesRead = getline(&line, &lineLength, filePtr);
        if (0 < bytesRead)
        {
            graphs[i].description = malloc(bytesRead + 1);
            if (NULL != graphs[i].description)
            {
                strncpy(graphs[i].description, line, bytesRead);
                graphs[i].description[bytesRead] = '\0';
                if (graphs[i].description[bytesRead - 1] == '\n')
                    graphs[i].description[bytesRead - 1] = '\0';
            }

#ifdef dbg
            printf("Additional graph information: %s\n", graphs[i].description);
#endif // dbg
        }
    }
    return graphs;
}

struct Graph *modularProduct(struct Graph *G, struct Graph *H){

    // 2. Write this function to multiply them :).
    /*
        1. Iterate over matrix G, over it's adjacencyLists

    */

};

int main(int argc, char *argv[])
{
    // Initialization
    if (2 != argc)
    {
        printf("Usage \n");
        return 1;
    }
    FILE *filePtr = fopen(argv[1], "rb");

    if (NULL == filePtr)
    {
        printf("Error: could not open file %s", argv[1]);
        return 1;
    }

    // Read graphs from file
    struct Graph *graphs = NULL;
    int noOfGraphs = 0;

    graphs = readGraphsFromFile(filePtr, &noOfGraphs);

    if (NULL == graphs)
        return -1;

    // Print graphs
    printGraphs(graphs, noOfGraphs);

    for (int i = 0; i < noOfGraphs; i++)
    {
        struct Node *temporaryNode = NULL;
        for (int j = 0; j < graphs[i].noOfVertices; j++)
        {

            while (NULL != graphs[i].adjacencyLists[j])
            {
                temporaryNode = graphs[i].adjacencyLists[j];
                graphs[i].adjacencyLists[j] = graphs[i].adjacencyLists[j]->nextNode;
                free(temporaryNode);
            }
        }
        free(graphs[i].adjacencyLists);
        free(graphs[i].description);
    }
    free(graphs);

    return 0;
}
