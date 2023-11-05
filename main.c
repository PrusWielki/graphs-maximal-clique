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
    if (NULL == node)
    {
        printf("Error: Couldn't allocate memory for a new node\n");
        return NULL;
    }
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
    int bytesRead = 0;
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
    if (NULL == graphs)
    {
        printf("Error: Couldn't allocate memory for graphs\n");
        return NULL;
    }
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
        if (NULL == graphs[i].adjacencyLists)
        {
            printf("Error: Couldn't allocate memory for new adjacency lists\n");
            return NULL;
        }

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
                        if (NULL == node)
                        {
                            printf("Error: Couldn't add a new node\n");
                            return NULL;
                        }
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
            graphs[i].description = malloc(sizeof(char) * (bytesRead + 1));
            if (NULL == graphs[i].description)
            {
                printf("Error: Couldn't allocate memory for graph description\n");
                return NULL;
            }

            strncpy(graphs[i].description, line, bytesRead);
            graphs[i].description[bytesRead] = '\0';
            if (graphs[i].description[bytesRead - 1] == '\n')
                graphs[i].description[bytesRead - 1] = '\0';

#ifdef dbg
            printf("Additional graph information: %s\n", graphs[i].description);
#endif // dbg
        }
        else
        {
            graphs[i].description = malloc(sizeof(char));
            if (NULL == graphs[i].description)
            {
                printf("Error: Couldn't allocate memory for graph description\n");
                return NULL;
            }
            graphs[i].description[0] = '\0';
        }
    }
    return graphs;
}

int isVertexInsideList(struct Node *iterator, int desiredVertex)
{
    while (NULL != iterator)
    {
        if (iterator->vertex == desiredVertex)
            return 1;
        iterator = iterator->nextNode;
    }
    return 0;
}

struct Graph *modularProduct(struct Graph *G, struct Graph *H)
{
    /*
        1. Iterate over matrix G, over it's adjacencyLists
        2. For each AdjacencyList of graph G:
            1. Iterate over AdjacencyLists from graph H
            2. Take element from Adjacency list from graph G, for each element from adjacency list from graph H it will have an edge, Push it to graph's GxH adjacency list
        3. So far we would have all multiplied elements with condition 1. "u is adjacent with u' and v is adjacent with v'"
        4. The above is DONE, what's left is: Need to figure out a way to add edges that satisfy the second condition: 'u is not adjacent with u' and v is not adjacent with v''
            1. Keeping in mind that: Any two vertices (u, v) and (u' , v' ) are adjacent in the modular product of G and H if and only if u is distinct from u', v is distinct from v'
            2. The way I would do this is to:
                1. Iterate over all vertices of GH, by creating two for loops iterating over vertices of G and H
                2. If vertex from GH (indexed  by the two new for loops) corresponding to given graph is not present in that graphs's adjacency list and same for the other graph then add that vertex to adjacency list as long as it satisfies the distinct condition (4.1)
        5. TODO: Only potentially: Efficiency perhaps could be improved. When we check if a vertex is not in given adjacency list then also maybe one could check if it's in both instead of doing it separately.
        6. DONE: Handle multigraphs. Edges should be in both directions.
    */
    if (NULL == G || NULL == H || NULL == G->adjacencyLists || NULL == H->adjacencyLists)
    {
        printf("Error: Couldn't multiply matrices, given matrices don't contain enough information\n");
        return NULL;
    }

    struct Graph *GH = malloc(sizeof(struct Graph *));

    if (NULL == GH)
    {
        printf("Error: Couldn't allocate memory for graph product\n");
        return NULL;
    }
    GH->description = malloc(sizeof(char));
    if (NULL == GH->description)
    {
        printf("Error: Couldn't allocate memory for graph product description\n");
        return NULL;
    }
    GH->description[0] = '\0';
    GH->noOfVertices = G->noOfVertices * H->noOfVertices;

    GH->adjacencyLists = malloc(GH->noOfVertices * sizeof(struct Node *));

    if (NULL == GH->adjacencyLists)
    {
        printf("Error: Couldn't allocate memory for graph product adjacency lists\n");
        return NULL;
    }

    for (int i = 0; i < G->noOfVertices; i++) // 1. 2.
    {
        for (int j = 0; j < H->noOfVertices; j++) // 2.1
        {
            GH->adjacencyLists[i * H->noOfVertices + j] = NULL;
            for (int k = 0; k < G->noOfVertices; k++) // 4.1.2
            {
                if (k != i && !isVertexInsideList(G->adjacencyLists[i], k) && !isVertexInsideList(G->adjacencyLists[k], i))
                {
                    for (int l = 0; l < H->noOfVertices; l++)
                    {

                        if (j != l && !isVertexInsideList(H->adjacencyLists[j], l) && !isVertexInsideList(H->adjacencyLists[l], j))
                        {
                            struct Node *node = newNode(k * H->noOfVertices + l, 1);
                            if (NULL == node)
                            {
                                printf("Error: Couldn't add a new node\n");
                                return NULL;
                            }
                            node->nextNode = GH->adjacencyLists[i * H->noOfVertices + j];
                            GH->adjacencyLists[i * H->noOfVertices + j] = node;
                        }
                    }
                }
            }

            struct Node *iterator_G = G->adjacencyLists[i];

            while (NULL != iterator_G)
            {
                if (isVertexInsideList(G->adjacencyLists[iterator_G->vertex], i))
                {

                    struct Node *iterator_H = H->adjacencyLists[j];
                    while (NULL != iterator_H)
                    {
                        if (isVertexInsideList(H->adjacencyLists[iterator_H->vertex], j))
                        {
#ifdef dbg
                            // printf("Would add edge from (%d,%d) to: (%d,%d)\n", i + 1, j + 1, iterator_G->vertex + 1, iterator_H->vertex + 1);
                            printf("Would add edge from %d to: %d\n", i * H->noOfVertices + j, iterator_G->vertex * H->noOfVertices + iterator_H->vertex);
#endif

                            struct Node *node = newNode(iterator_G->vertex * H->noOfVertices + iterator_H->vertex, iterator_G->weight * iterator_H->weight); // 2.2
                            if (NULL == node)
                            {
                                printf("Error: Couldn't add a new node\n");
                                return NULL;
                            }
                            node->nextNode = GH->adjacencyLists[i * H->noOfVertices + j];
                            GH->adjacencyLists[i * H->noOfVertices + j] = node;
                        }
                        iterator_H = iterator_H->nextNode;
                    }
                }
                iterator_G = iterator_G->nextNode;
#ifdef dbg
                printf("Value of iterator_H: %d\n", iterator_H);
#endif // dbg
            }
        }
    }
    return GH;
};

void bronKerbosch()
{

    /*
        1. TODO: Write a function to transform a directed graph to undirected graph (just remove the single edges)
        2. TODO: Write needed datastructures to hold vertices, I guess we could use a List to dynamically store a list of vertices, or we could implement a vector.
        3. TODO: Write the Bron-Kerbosch
        4. TODO: Test it.
    */
}

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

    // Modular Graph Product

    struct Graph *GH = modularProduct(graphs, graphs + 1);

    printGraph(*GH);

    // TODO: Free memory from product graph

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
