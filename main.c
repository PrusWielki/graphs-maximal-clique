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

struct Vector
{
    int *data;
    int size;
    int currentNumberOfElements;
} Vector;

int createVector(struct Vector *newVector, int size)
{
    /*
        Accepts a pointer to already allocated memory for struct Vector
    */
    if (NULL == newVector)
        return -1;
    newVector->data = malloc(size * sizeof(int));
    if (NULL == newVector->data)
        return -1;
    newVector->currentNumberOfElements = 0;
    newVector->size = size;
    return 1;
}
int pushBackVector(struct Vector *vector, int value)
{
    if (NULL == vector || NULL == vector->data)
        return -1;
    if (vector->currentNumberOfElements == vector->size)
    {
        int *newArray = malloc(sizeof(int) * 2 * vector->size);
        if (NULL == newArray)
            return -1;

        for (int i = 0; i < vector->currentNumberOfElements; i++)
        {
            newArray[i] = vector->data[i];
        }

        free(vector->data);
        vector->data = newArray;
        vector->size = 2 * vector->size;
    }
    if (NULL != vector->data)
    {
        vector->data[vector->currentNumberOfElements] = value;
        vector->currentNumberOfElements = vector->currentNumberOfElements + 1;
    }
    return 1;
}

int removeElementVector(struct Vector *vector, int value)
{
    if (NULL == vector || NULL == vector->data)
        return -1;
    for (int i = 0; i < vector->currentNumberOfElements; i++)
    {
        if (vector->data[i] == value)
        {
            for (int j = i; j < vector->currentNumberOfElements - 1; j++)
            {
                vector->data[j] = vector->data[j + 1];
            }
            vector->currentNumberOfElements = vector->currentNumberOfElements - 1;
            return 1;
        }
    }
    return -1;
}

int findElementVector(struct Vector *vector, int value)
{
    /*
        -1 if no element found
        index if element found
    */
    if (NULL == vector || NULL == vector->data)
        return -1;
    for (int i = 0; i < vector->currentNumberOfElements; i++)
    {
        if (vector->data[i] == value)
            return i;
    }
    return -1;
}
void printVector(struct Vector vector)
{
    if (NULL == vector.data)
        return;
    printf("[ ");
    for (int i = 0; i < vector.currentNumberOfElements; i++)
    {
        printf("%d ", vector.data[i]);
    }
    printf("]\n");
}
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

void removeNode(struct Node **head, int vertexToRemove)
{

    /*
        DONE
        1. Two variables, current and previous.
        2. Special case when the vertexToRemove is the first in the list.
            1. Point head to the next element and free the memory.
        3. Previous should point to the next, and current should be freed.
    */

    struct Node *current = *head;
    struct Node *previous = *head;

    int index = 0;
    while (NULL != current)
    {
        current = current->nextNode;
        if (0 == index && vertexToRemove == previous->vertex)
        {
            *head = previous->nextNode;
            free(previous);
            break;
        }
        if (vertexToRemove == current->vertex)
        {
            previous->nextNode = current->nextNode;
            free(current);
            break;
        }

        previous = previous->nextNode;
        index++;
    }
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
        printf("New adj list[0]: %d\n", graphs[i].adjacencyLists[0]);
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
                    printf("new vertex in adj list: %d\n", graphs[i].adjacencyLists[j * graphs[i].noOfVertices + k]);
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
        DONE
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
        6. DONE: Handle directed graphs. Edges should be in both directions.
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
                printf("Value of iterator_G: %d\n", iterator_G);
#endif // dbg
            }
        }
    }
    return GH;
};

struct Graph toUndirectedGraph(struct Graph G)
{

    /*
        DONE
        1. DONE: Write a function to remove a node from a list.
        2. Iterate over all adjacency lists.
            1. For each adjacency list, for each node, check if there is an edge in the other direction.
                1. If not remove the node.
        3. Return the resulting new graph.
    */

    for (int i = 0; i < G.noOfVertices; i++)
    {
        if (NULL == G.adjacencyLists[i])
            continue;
        struct Node *iterator = G.adjacencyLists[i];
        while (NULL != iterator)
        {
#ifdef dbg
            printf("List: %d, vertex: %d\n", i, iterator->vertex);
#endif
            if (NULL == G.adjacencyLists[iterator->vertex] || !isVertexInsideList(G.adjacencyLists[iterator->vertex], i))
            {
#ifdef dbg
                printf("Removing vertex %d from list %d\n", iterator->vertex, i);
#endif
                removeNode(&G.adjacencyLists[i], iterator->vertex);
            }
            iterator = iterator->nextNode;
        }
    }
    return G;
}

void bronKerbosch(struct Vector R, struct Vector P, struct Vector X, struct Graph *graph)
{
    /*
        1. DONE: Write a function to transform a directed graph to undirected graph (just remove the single edges)
        2. DONE: Write needed datastructures to hold vertices, I guess we could use a List to dynamically store a list of vertices, or we could implement a vector.
        3. DONE: Write the Bron-Kerbosch
        4. TODO: Test it.
        5. TODO: Free memory, use valgrind :)
    */
#ifdef dbg
    printVector(R);
    printVector(P);
    printVector(X);
    printf("\n");
#endif
    if (0 == P.currentNumberOfElements && 0 == X.currentNumberOfElements)
    {
        printf("Maximal Clique: ");
        printVector(R);
        return;
    }
    struct Node *iterator = NULL;
    int pivot = -1;
    if (0 < P.currentNumberOfElements)
        pivot = P.data[0];

    else if (0 < X.currentNumberOfElements)
        pivot = X.data[0];

    struct Vector toIterateOver;
    createVector(&toIterateOver, P.currentNumberOfElements);
    for (int i = 0; i < P.currentNumberOfElements; i++)
    {
        pushBackVector(&toIterateOver, P.data[i]);
    }
    if (-1 != pivot)
    {
        iterator = graph->adjacencyLists[pivot];
        while (NULL != iterator)
        {
            removeElementVector(&toIterateOver, iterator->vertex);
            iterator = iterator->nextNode;
        }
    }

    int i = 0;
    while (0 < toIterateOver.currentNumberOfElements)
    {
        // R ⋃ {v}
        struct Vector rPlusV;
        createVector(&rPlusV, R.currentNumberOfElements + 1);
        for (int j = 0; j < R.currentNumberOfElements; j++)
        {
            pushBackVector(&rPlusV, R.data[j]);
        }

        pushBackVector(&rPlusV, toIterateOver.data[i]);
#ifdef dbg
        printVector(R);
        printVector(P);
        printVector(X);
        printf("%d\n", P.data[i]);
#endif
        // P ⋂ N(v)
        struct Vector pAndVEdges;
        createVector(&pAndVEdges, P.size);
        iterator = graph->adjacencyLists[toIterateOver.data[i]];
        for (int j = 0; j < P.currentNumberOfElements; j++)
        {
            if (isVertexInsideList(iterator, P.data[j]))
            {
                pushBackVector(&pAndVEdges, P.data[j]);
            }
        }

        // X ⋂ N(v)
        struct Vector xAndVEdges;
        createVector(&xAndVEdges, X.size);
        iterator = graph->adjacencyLists[toIterateOver.data[i]];
        for (int j = 0; j < X.currentNumberOfElements; j++)
        {
            if (isVertexInsideList(iterator, X.data[j]))
            {
                pushBackVector(&xAndVEdges, X.data[j]);
            }
        }

#ifdef dbg
        printVector(rPlusV);
        printVector(pAndVEdges);
        printVector(xAndVEdges);
        printf("\n");
#endif
        // BronKerbosch2(R ⋃ {v}, P ⋂ N(v), X ⋂ N(v))
        bronKerbosch(rPlusV, pAndVEdges, xAndVEdges, graph);

        // X := X ⋃ {v}
        pushBackVector(&X, toIterateOver.data[i]);

#ifdef dbg
        printf("Removed: %d\n", P.data[i]);
#endif
        // P := P \ {v}
        removeElementVector(&P, toIterateOver.data[i]);
        removeElementVector(&toIterateOver, toIterateOver.data[i]);
#ifdef dbg
        printVector(P);
        printf("\n");
#endif
    }
    return;
}

void dbgTests(struct Graph directedGraph)
{

    // Remove from list test

    struct Node *newList = NULL;
    for (int i = 0; i < 4; i++)
    {
        struct Node *node = newNode(i, i);
        if (NULL == node)
        {
            printf("Error: Couldn't add a new node\n");
            return;
        }
        node->nextNode = newList;
        newList = node;
    }

    removeNode(&newList, 0);
    while (newList != NULL)
    {
        printf("%d\n", newList->vertex);
        newList = newList->nextNode;
    }
    // ----------------------------

    // To undirected graph
    struct Graph undirectedGraph = toUndirectedGraph(directedGraph);
    printGraph(undirectedGraph);

    // ----------------------------

    // Vector tests

    struct Vector *newVector = malloc(sizeof(struct Vector));

    createVector(newVector, 2);
    pushBackVector(newVector, 1);
    pushBackVector(newVector, 2);
    pushBackVector(newVector, 3);
    for (int i = 0; i < newVector->currentNumberOfElements; i++)
    {
        printf("Vector: index: %d value: %d\n", i, newVector->data[i]);
    }
    printf("Vector number of elements %d\n", newVector->currentNumberOfElements);
    printf("Vector size %d\n", newVector->size);

    removeElementVector(newVector, 3);
    for (int i = 0; i < newVector->currentNumberOfElements; i++)
    {
        printf("Vector: index: %d value: %d\n", i, newVector->data[i]);
    }
    printf("Vector number of elements %d\n", newVector->currentNumberOfElements);
    printf("Vector size %d\n", newVector->size);

    printf("Element %d found at index %d\n", 2, findElementVector(newVector, 2));
    printf("Element %d found at index %d\n", 3, findElementVector(newVector, 3));
}

int main(int argc, char *argv[])
{
    /*
        1. DONE: Read all input graphs from a single file.
        2. DONE: Iterate over them and for each print maximal cliques.
        3. DONE: Multiply all of them and find maximal clique - that will be a maximal common subgraph.
        4. TODO: Instead of printing all the results in BronKerbosch, store them in a pointer and then process it.
    */

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
    printf("-------------------------------------------------\n");
    for (int i = 0; i < noOfGraphs; i++)
    {
        printf("-------------------------------------------------\n");
        printf("Maximal cliques for graph %d\n", i);
        struct Vector R;
        createVector(&R, 1);
        struct Vector P;
        createVector(&P, graphs[i].noOfVertices);
#ifdef dbg
        printf("graph size: %d\n", graphs[i].noOfVertices);
#endif
        for (int j = 0; j < graphs[i].noOfVertices; j++)
        {
            pushBackVector(&P, j);
#ifdef dbg
            printVector(P);
#endif
        }

        struct Vector X;
        createVector(&X, 1);
        struct Graph undirectedGraph = toUndirectedGraph(graphs[i]);
        bronKerbosch(R, P, X, &undirectedGraph);
    }
    printf("-------------------------------------------------\n");
    // Modular Graph Product

    struct Graph *GH = NULL;

    if (1 < noOfGraphs)
    {

        GH = graphs;
        for (int i = 1; i < noOfGraphs; i++)
        {
            GH = modularProduct(GH, graphs + i);
        }

        if (NULL != GH)
        {
            printf("-------------------------------------------------\n");
            printf("Modular product graph of all input graphs:\n");
            printGraph(*GH);
            struct Vector R;
            createVector(&R, 1);
            struct Vector P;
            createVector(&P, 1);
            for (int i = 0; i < GH->noOfVertices; i++)
            {
                pushBackVector(&P, i);
            }
            struct Vector X;
            createVector(&X, 1);

            printf("-------------------------------------------------\n");
            printf("Maximal common subgraph candidates of all input graphs:\n");

            bronKerbosch(R, P, X, GH);
        }
    }
#ifdef dbg
    dbgTests(graphs[0]);
#endif // dbg

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
