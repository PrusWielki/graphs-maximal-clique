#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// #define PRINTTOCMD
// #define dbg
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

int createVector_Int(struct Vector *newVector, int size)
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

int createVector_Graph(struct Vector *newVector, int size)
{
    /*
        Accepts a pointer to already allocated memory for struct Vector
    */
    if (NULL == newVector)
        return -1;
    newVector->data = malloc(size * sizeof(struct Graph));
    if (NULL == newVector->data)
        return -1;
    newVector->currentNumberOfElements = 0;
    newVector->size = size;
    return 1;
}

int createVector_Vector(struct Vector *newVector, int size)
{
    /*
        Accepts a pointer to already allocated memory for struct Vector
    */
    if (NULL == newVector)
        return -1;
    newVector->data = malloc(size * sizeof(struct Vector));
    if (NULL == newVector->data)
        return -1;
    newVector->currentNumberOfElements = 0;
    newVector->size = size;
    return 1;
}

int pushBackVector_Int(struct Vector *vector, int value)
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
            newArray[i] = *((int *)vector->data + i);
        }

        free(vector->data);
        vector->data = newArray;
        vector->size = 2 * vector->size;
    }
    if (NULL != vector->data)
    {
        *((int *)vector->data + vector->currentNumberOfElements) = value;
        vector->currentNumberOfElements = vector->currentNumberOfElements + 1;
    }
    return 1;
}

int pushBackVector_Vector(struct Vector *vector, struct Vector value)
{
    if (NULL == vector || NULL == vector->data)
        return -1;
    if (vector->currentNumberOfElements == vector->size)
    {
        struct Vector *newArray = malloc(sizeof(struct Vector) * 2 * vector->size);
        if (NULL == newArray)
            return -1;

        for (int i = 0; i < vector->currentNumberOfElements; i++)
        {
            newArray[i] = *((struct Vector *)vector->data + i);
        }

        free(vector->data);
        vector->data = newArray;
        vector->size = 2 * vector->size;
    }
    if (NULL != vector->data)
    {
        *((struct Vector *)vector->data + vector->currentNumberOfElements) = value;
        vector->currentNumberOfElements = vector->currentNumberOfElements + 1;
    }
    return 1;
}

int pushBackVector_Graph(struct Vector *vector, struct Graph value)
{
    if (NULL == vector || NULL == vector->data)
        return -1;
    if (vector->currentNumberOfElements == vector->size)
    {
        struct Graph *newArray = malloc(sizeof(struct Graph) * 2 * vector->size);
        if (NULL == newArray)
            return -1;

        for (int i = 0; i < vector->currentNumberOfElements; i++)
        {
            newArray[i] = *((struct Graph *)vector->data + i);
        }

        free(vector->data);
        vector->data = newArray;
        vector->size = 2 * vector->size;
    }
    if (NULL != vector->data)
    {
        *((struct Graph *)vector->data + vector->currentNumberOfElements) = value;
        vector->currentNumberOfElements = vector->currentNumberOfElements + 1;
    }
    return 1;
}

int removeElementVector_Int(struct Vector *vector, int value)
{
    if (NULL == vector || NULL == vector->data)
        return -1;
    for (int i = 0; i < vector->currentNumberOfElements; i++)
    {
        if (*((int *)vector->data + i) == value)
        {
            for (int j = i; j < vector->currentNumberOfElements - 1; j++)
            {
                *((int *)vector->data + j) = *((int *)vector->data + j + 1);
            }
            vector->currentNumberOfElements = vector->currentNumberOfElements - 1;
            return 1;
        }
    }
    return -1;
}

int findElementVector_Int(struct Vector *vector, int value)
{
    /*
        -1 if no element found
        index if element found
    */
    if (NULL == vector || NULL == vector->data)
        return -1;
    for (int i = 0; i < vector->currentNumberOfElements; i++)
    {
        if (*((int *)vector->data + i) == value)
            return i;
    }
    return -1;
}
struct Vector popVector_Vector(struct Vector *vector)
{

    struct Vector pop = *((struct Vector *)(vector->data) + vector->currentNumberOfElements - 1);
    vector->currentNumberOfElements = vector->currentNumberOfElements - 1;
    return pop;
}
void printVector_Int(struct Vector vector)
{
    if (NULL == vector.data)
        return;
    printf("[ ");
    for (int i = 0; i < vector.currentNumberOfElements; i++)
    {
        printf("%d ", *((int *)vector.data + i));
    }
    printf("]\n");
}

void printVector_Vector(struct Vector vector)
{
    if (NULL == vector.data)
        return;

    for (int i = 0; i < vector.currentNumberOfElements; i++)
    {
        printf("[ ");
        for (int j = 0; j < ((struct Vector *)(vector.data) + i)->currentNumberOfElements; j++)
        {
            printf("%d ", *(((int *)((struct Vector *)(vector.data) + i)->data) + j));
        }

        printf("]\n");
    }
}
void printVector_Vector_Max(struct Vector vector)
{
    if (NULL == vector.data)
        return;

    int max = 0;
    for (int i = 0; i < vector.currentNumberOfElements; i++)
    {

        if (max < ((struct Vector *)(vector.data) + i)->currentNumberOfElements)
            max = ((struct Vector *)(vector.data) + i)->currentNumberOfElements;
    }
    for (int i = 0; i < vector.currentNumberOfElements; i++)
    {
        if (max != ((struct Vector *)(vector.data) + i)->currentNumberOfElements)
            continue;
        printf("[ ");

        for (int j = 0; j < ((struct Vector *)(vector.data) + i)->currentNumberOfElements; j++)
        {
            printf("%d ", *(((int *)((struct Vector *)(vector.data) + i)->data) + j));
        }

        printf("]\n");
    }
}

int saveToFileVector_Vector(struct Vector vector, FILE *fptr)
{

    if (NULL == vector.data || NULL == fptr)
        return -1;

    for (int i = 0; i < vector.currentNumberOfElements; i++)
    {
        fprintf(fptr, "[ ");
        for (int j = 0; j < ((struct Vector *)(vector.data) + i)->currentNumberOfElements; j++)
        {
            fprintf(fptr, "%d ", *(((int *)((struct Vector *)(vector.data) + i)->data) + j));
        }

        fprintf(fptr, "]\n");
    }

    return 1;
}

int saveToFileVector_Vector_Max(struct Vector vector, FILE *fptr)
{

    if (NULL == vector.data || NULL == fptr)
        return -1;
    int max = 0;
    for (int i = 0; i < vector.currentNumberOfElements; i++)
    {

        if (max < ((struct Vector *)(vector.data) + i)->currentNumberOfElements)
            max = ((struct Vector *)(vector.data) + i)->currentNumberOfElements;
    }
    for (int i = 0; i < vector.currentNumberOfElements; i++)
    {
        if (max != ((struct Vector *)(vector.data) + i)->currentNumberOfElements)
            continue;
        fprintf(fptr, "[ ");
        for (int j = 0; j < ((struct Vector *)(vector.data) + i)->currentNumberOfElements; j++)
        {
            fprintf(fptr, "%d ", *(((int *)((struct Vector *)(vector.data) + i)->data) + j));
        }

        fprintf(fptr, "]\n");
    }

    return 1;
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
void freeGraph(struct Graph *graph)
{
    if (NULL == graph)
        return;

    struct Node *temporaryNode = NULL;
    for (int j = 0; j < graph->noOfVertices; j++)
    {

        while (NULL != graph->adjacencyLists[j])
        {
            temporaryNode = graph->adjacencyLists[j];
            graph->adjacencyLists[j] = graph->adjacencyLists[j]->nextNode;
            free(temporaryNode);
        }
    }
    free(graph->adjacencyLists);
    free(graph->description);
}
void readGraphsFromFile(FILE *filePtr, int *noOfGraphs, struct Vector *graphsVector)
{

    size_t lineLength = 0;
    char *line = NULL;
    int bytesRead = 0;
    int noOfVertices = 0;
    int noOfGraphsInFile = 0;

    // Read number of graphs in a file
    bytesRead = getline(&line, &lineLength, filePtr);

    if (0 < bytesRead)
    {
        noOfGraphsInFile = strtol(line, NULL, 10);

#ifdef dbg
        printf("file: %s\n", line);
        printf("Graphs: %d\n", noOfGraphsInFile);
#endif // dbg
    }

    // struct Graph *graphs = malloc(noOfGraphsInFile * sizeof(Graph));

    for (int i = 0; i < noOfGraphsInFile; i++)
    {

        bytesRead = getline(&line, &lineLength, filePtr);

        if (0 >= bytesRead)
            continue;
        struct Graph newGraph;
        noOfVertices = strtol(line, NULL, 10);
        newGraph.noOfVertices = noOfVertices;
#ifdef dbg
        printf("file: %s\n", line);
        printf("Vertices in graph %d: %d \n", i, newGraph.noOfVertices);
#endif // dbg

        newGraph.adjacencyLists = malloc(noOfVertices * sizeof(struct Node *));
        if (NULL == newGraph.adjacencyLists)
        {
            printf("Error: Couldn't allocate memory for new adjacency lists\n");
            return;
        }

#ifdef dbg
        printf("New adj list[0]: %d\n", newGraph.adjacencyLists[0]);
#endif // dbg
        for (int j = 0; j < noOfVertices; j++)
        {
            newGraph.adjacencyLists[j] = NULL;
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
                            return;
                        }
                        node->nextNode = newGraph.adjacencyLists[j];
                        newGraph.adjacencyLists[j] = node;
                    }

#ifdef dbg
                    printf("file: %s\n", ptr);
                    printf("new vertex in adj list: %d\n", newGraph.adjacencyLists[j * newGraph.noOfVertices + k]);
#endif // dbg
                    ptr = strtok(NULL, " ");
                    k++;
                }
            }
        }

        bytesRead = getline(&line, &lineLength, filePtr);
        if (0 < bytesRead)
        {
            newGraph.description = malloc(sizeof(char) * (bytesRead + 1));
            if (NULL == newGraph.description)
            {
                printf("Error: Couldn't allocate memory for graph description\n");
                return;
            }

            strncpy(newGraph.description, line, bytesRead);
            newGraph.description[bytesRead] = '\0';
            if (newGraph.description[bytesRead - 1] == '\n')
                newGraph.description[bytesRead - 1] = '\0';

#ifdef dbg
            printf("Additional graph information: %s\n", newGraph.description);
#endif // dbg
        }
        else
        {
            newGraph.description = malloc(sizeof(char));
            if (NULL == newGraph.description)
            {
                printf("Error: Couldn't allocate memory for graph description\n");
                return;
            }
            newGraph.description[0] = '\0';
        }

        pushBackVector_Graph(graphsVector, newGraph);
    }
    *noOfGraphs = *noOfGraphs + noOfGraphsInFile;
    free(line);
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

    struct Graph *GH = malloc(sizeof(struct Graph));

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

void toUndirectedGraph(struct Graph G)
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
        struct Node *next_iterator = NULL;
        while (NULL != iterator)
        {
#ifdef dbg
            printf("List: %d, vertex: %d\n", i, iterator->vertex);
#endif
            if (i == iterator->vertex || NULL == G.adjacencyLists[iterator->vertex] || !isVertexInsideList(G.adjacencyLists[iterator->vertex], i))
            {
#ifdef dbg
                printf("Removing vertex %d from list %d\n", iterator->vertex, i);
#endif
                next_iterator = iterator->nextNode;
                removeNode(&G.adjacencyLists[i], iterator->vertex);
                iterator = next_iterator;
            }
            else
                iterator = iterator->nextNode;
        }
    }
}

int bronKerbosch(struct Vector R, struct Vector P, struct Vector X, struct Graph *graph, struct Vector *bronResult)
{
    /*
        1. DONE: Write a function to transform a directed graph to undirected graph (just remove the single edges)
        2. DONE: Write needed datastructures to hold vertices, I guess we could use a List to dynamically store a list of vertices, or we could implement a vector.
        3. DONE: Write the Bron-Kerbosch
        4. TODO: Test it.
        5. TODO: Free memory, use valgrind :)
    */
#ifdef dbg
    printVector_Int(R);
    printVector_Int(P);
    printVector_Int(X);
    printf("\n");
#endif
    if (0 == P.currentNumberOfElements && 0 == X.currentNumberOfElements)
    {
        // printf("Maximal Clique: ");
        // printVector_Int(R);
        pushBackVector_Vector(bronResult, R);
        free(P.data);

        free(X.data);
        return 1;
    }
    struct Node *iterator = NULL;
    int pivot = -1;
    if (0 < P.currentNumberOfElements)
        pivot = *((int *)P.data);

    else if (0 < X.currentNumberOfElements)
        pivot = *((int *)X.data);

    struct Vector toIterateOver;
    createVector_Int(&toIterateOver, P.currentNumberOfElements);
    for (int i = 0; i < P.currentNumberOfElements; i++)
    {

        pushBackVector_Int(&toIterateOver, *((int *)P.data + i));
    }
    if (-1 != pivot)
    {
        iterator = graph->adjacencyLists[pivot];
        while (NULL != iterator)
        {
            removeElementVector_Int(&toIterateOver, iterator->vertex);
            iterator = iterator->nextNode;
        }
    }

    int i = 0;
    while (0 < toIterateOver.currentNumberOfElements)
    {
        // R ⋃ {v}
        struct Vector rPlusV;
        createVector_Int(&rPlusV, R.currentNumberOfElements + 1);
        for (int j = 0; j < R.currentNumberOfElements; j++)
        {
            pushBackVector_Int(&rPlusV, *((int *)R.data + j));
        }

        pushBackVector_Int(&rPlusV, *((int *)toIterateOver.data + i));
#ifdef dbg
        printVector_Int(R);
        printVector_Int(P);
        printVector_Int(X);
        printf("%d\n", *((int *)P.data + i));
#endif
        // P ⋂ N(v)
        struct Vector pAndVEdges;
        createVector_Int(&pAndVEdges, P.size);
        iterator = graph->adjacencyLists[*((int *)toIterateOver.data + i)];
        for (int j = 0; j < P.currentNumberOfElements; j++)
        {
            if (isVertexInsideList(iterator, *((int *)P.data + j)))
            {
                pushBackVector_Int(&pAndVEdges, *((int *)P.data + j));
            }
        }

        // X ⋂ N(v)
        struct Vector xAndVEdges;
        createVector_Int(&xAndVEdges, X.size);
        iterator = graph->adjacencyLists[*((int *)toIterateOver.data + i)];
        for (int j = 0; j < X.currentNumberOfElements; j++)
        {
            if (isVertexInsideList(iterator, *((int *)X.data + j)))
            {
                pushBackVector_Int(&xAndVEdges, *((int *)X.data + j));
            }
        }

#ifdef dbg
        printVector_Int(rPlusV);
        printVector_Int(pAndVEdges);
        printVector_Int(xAndVEdges);
        printf("\n");
#endif
        // BronKerbosch2(R ⋃ {v}, P ⋂ N(v), X ⋂ N(v))
        bronKerbosch(rPlusV, pAndVEdges, xAndVEdges, graph, bronResult);

        // X := X ⋃ {v}
        pushBackVector_Int(&X, *((int *)toIterateOver.data + i));

#ifdef dbg
        printf("Removed: %d\n", *((int *)P.data + i));
#endif
        // P := P \ {v}
        removeElementVector_Int(&P, *((int *)toIterateOver.data + i));
        removeElementVector_Int(&toIterateOver, *((int *)toIterateOver.data + i));
#ifdef dbg
        printVector_Int(P);
        printf("\n");
#endif
        // free(pAndVEdges.data);
        // if (!result)
        // free(rPlusV.data);
        // free(xAndVEdges.data);
    }
    free(P.data);
    free(R.data);
    free(X.data);
    free(toIterateOver.data);
    return 0;
}
int iterBronKerbosch(struct Vector R, struct Vector P, struct Vector X, struct Graph *graph, struct Vector *bronResult)
{
    /*
        1. DONE: Write a function to transform a directed graph to undirected graph (just remove the single edges)
        2. DONE: Write needed datastructures to hold vertices, I guess we could use a List to dynamically store a list of vertices, or we could implement a vector.
        3. DONE: Write the Bron-Kerbosch
        4. TODO: Test it.
        5. TODO: Free memory, use valgrind :)
    */
#ifdef dbg
    printVector_Int(R);
    printVector_Int(P);
    printVector_Int(X);
    printf("\n");
#endif

    struct Vector stack;
    createVector_Vector(&stack, 3);
    pushBackVector_Vector(&stack, R);
    pushBackVector_Vector(&stack, P);
    pushBackVector_Vector(&stack, X);
    struct Node *iterator = NULL;

    while (0 < stack.currentNumberOfElements)
    {
        struct Vector currentX = popVector_Vector(&stack);
        struct Vector currentP = popVector_Vector(&stack);
        struct Vector currentR = popVector_Vector(&stack);
        if (0 == currentP.currentNumberOfElements && 0 == currentX.currentNumberOfElements)
        {
            // printf("Maximal Clique: ");
            // printVector_Int(R);
            pushBackVector_Vector(bronResult, currentR);
        }

        if (0 < currentP.currentNumberOfElements)
        {

            struct Vector pNotV;
            createVector_Int(&pNotV, currentP.currentNumberOfElements - 1);
            for (int j = 1; j < currentP.currentNumberOfElements; j++)
            {
                pushBackVector_Int(&pNotV, *((int *)currentP.data + j));
            }
            struct Vector xAndV;
            createVector_Int(&xAndV, currentX.currentNumberOfElements + 1);
            for (int j = 1; j < currentX.currentNumberOfElements; j++)
            {
                pushBackVector_Int(&xAndV, *((int *)currentX.data + j));
            }
            pushBackVector_Int(&xAndV, *((int *)currentP.data));

            struct Vector rPlusV;
            createVector_Int(&rPlusV, currentR.currentNumberOfElements + 1);
            for (int j = 0; j < currentR.currentNumberOfElements; j++)
            {
                pushBackVector_Int(&rPlusV, *((int *)currentR.data + j));
            }

            pushBackVector_Int(&rPlusV, *((int *)currentP.data));
            struct Vector pAndVEdges;
            createVector_Int(&pAndVEdges, currentP.size);
            iterator = graph->adjacencyLists[*((int *)currentP.data)];
            for (int j = 0; j < currentP.currentNumberOfElements; j++)
            {
                if (isVertexInsideList(iterator, *((int *)currentP.data + j)))
                {
                    pushBackVector_Int(&pAndVEdges, *((int *)currentP.data + j));
                }
            }

            struct Vector xAndVEdges;
            createVector_Int(&xAndVEdges, currentX.size);
            iterator = graph->adjacencyLists[*((int *)currentP.data)];
            for (int j = 0; j < currentX.currentNumberOfElements; j++)
            {
                if (isVertexInsideList(iterator, *((int *)currentX.data + j)))
                {
                    pushBackVector_Int(&xAndVEdges, *((int *)currentX.data + j));
                }
            }

            // copy R!!
            struct Vector newR;
            createVector_Int(&newR, R.currentNumberOfElements);
            for (int i = 0; i < R.currentNumberOfElements; i++)
            {
                *((int *)newR.data + i) = *((int *)R.data + i);
            }

            pushBackVector_Vector(&stack, newR);
            pushBackVector_Vector(&stack, pNotV);
            pushBackVector_Vector(&stack, xAndV);
            pushBackVector_Vector(&stack, rPlusV);
            pushBackVector_Vector(&stack, pAndVEdges);
            pushBackVector_Vector(&stack, xAndVEdges);

            removeElementVector_Int(&currentP, *(int *)currentP.data);
        }
        free(currentR.data);
        free(currentX.data);
        free(currentP.data);
    }

    free(R.data);
    return 0;
}
int iterPivotBronKerbosch(struct Vector R, struct Vector P, struct Vector X, struct Graph *graph, struct Vector *bronResult)
{
    /*
        1. DONE: Write a function to transform a directed graph to undirected graph (just remove the single edges)
        2. DONE: Write needed datastructures to hold vertices, I guess we could use a List to dynamically store a list of vertices, or we could implement a vector.
        3. DONE: Write the Bron-Kerbosch
        4. TODO: Test it.
        5. TODO: Free memory, use valgrind :)
    */
#ifdef dbg
    printVector_Int(R);
    printVector_Int(P);
    printVector_Int(X);
    printf("\n");
#endif

    struct Vector stack;
    createVector_Vector(&stack, 3);
    pushBackVector_Vector(&stack, R);
    pushBackVector_Vector(&stack, P);
    pushBackVector_Vector(&stack, X);

    while (0 < stack.currentNumberOfElements)
    {
        struct Vector currentX = popVector_Vector(&stack);
        struct Vector currentP = popVector_Vector(&stack);
        struct Vector currentR = popVector_Vector(&stack);
        if (0 == currentP.currentNumberOfElements && 0 == currentX.currentNumberOfElements)
        {
            // printf("Maximal Clique: ");
            // printVector_Int(R);
            pushBackVector_Vector(bronResult, currentR);
            continue;
        }
        struct Node *iterator = NULL;
        int pivot = -1;
        if (0 < currentP.currentNumberOfElements)
            pivot = *((int *)currentP.data);

        else if (0 < currentX.currentNumberOfElements)
            pivot = *((int *)currentX.data);

        struct Vector toIterateOver;
        createVector_Int(&toIterateOver, currentP.currentNumberOfElements);
        for (int i = 0; i < currentP.currentNumberOfElements; i++)
        {

            pushBackVector_Int(&toIterateOver, *((int *)currentP.data + i));
        }
        if (-1 != pivot)
        {
            iterator = graph->adjacencyLists[pivot];
            while (NULL != iterator)
            {
                removeElementVector_Int(&toIterateOver, iterator->vertex);
                iterator = iterator->nextNode;
            }
        }

        if (0 < toIterateOver.currentNumberOfElements)
        {

            struct Vector pNotV;
            createVector_Int(&pNotV, toIterateOver.currentNumberOfElements - 1);
            for (int j = 1; j < toIterateOver.currentNumberOfElements; j++)
            {
                pushBackVector_Int(&pNotV, *((int *)toIterateOver.data + j));
            }
            struct Vector xAndV;
            createVector_Int(&xAndV, currentX.currentNumberOfElements + 1);
            for (int j = 1; j < currentX.currentNumberOfElements; j++)
            {
                pushBackVector_Int(&xAndV, *((int *)currentX.data + j));
            }
            pushBackVector_Int(&xAndV, *((int *)toIterateOver.data));

            struct Vector rPlusV;
            createVector_Int(&rPlusV, currentR.currentNumberOfElements + 1);
            for (int j = 0; j < currentR.currentNumberOfElements; j++)
            {
                pushBackVector_Int(&rPlusV, *((int *)currentR.data + j));
            }

            pushBackVector_Int(&rPlusV, *((int *)toIterateOver.data));
            struct Vector pAndVEdges;
            createVector_Int(&pAndVEdges, toIterateOver.size);
            iterator = graph->adjacencyLists[*((int *)toIterateOver.data)];
            for (int j = 0; j < currentP.currentNumberOfElements; j++)
            {
                if (isVertexInsideList(iterator, *((int *)toIterateOver.data + j)))
                {
                    pushBackVector_Int(&pAndVEdges, *((int *)toIterateOver.data + j));
                }
            }

            struct Vector xAndVEdges;
            createVector_Int(&xAndVEdges, currentX.size);
            iterator = graph->adjacencyLists[*((int *)toIterateOver.data)];
            for (int j = 0; j < currentX.currentNumberOfElements; j++)
            {
                if (isVertexInsideList(iterator, *((int *)currentX.data + j)))
                {
                    pushBackVector_Int(&xAndVEdges, *((int *)currentX.data + j));
                }
            }

            // copy R!!
            struct Vector newR;
            createVector_Int(&newR, R.currentNumberOfElements);
            for (int i = 0; i < R.currentNumberOfElements; i++)
            {
                *((int *)newR.data + i) = *((int *)R.data + i);
            }

            pushBackVector_Vector(&stack, newR);
            pushBackVector_Vector(&stack, pNotV);
            pushBackVector_Vector(&stack, xAndV);
            pushBackVector_Vector(&stack, rPlusV);
            pushBackVector_Vector(&stack, pAndVEdges);
            pushBackVector_Vector(&stack, xAndVEdges);

            removeElementVector_Int(&currentP, *(int *)toIterateOver.data);
            removeElementVector_Int(&toIterateOver, *(int *)toIterateOver.data);
        }
        free(currentR.data);
        free(currentX.data);
        free(currentP.data);
    }

    free(R.data);
    return 0;
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
    toUndirectedGraph(directedGraph);
    printGraph(directedGraph);

    // ----------------------------

    // Vector tests

    struct Vector *newVector = malloc(sizeof(struct Vector));

    createVector_Int(newVector, 2);
    pushBackVector_Int(newVector, 1);
    pushBackVector_Int(newVector, 2);
    pushBackVector_Int(newVector, 3);
    for (int i = 0; i < newVector->currentNumberOfElements; i++)
    {
        printf("Vector: index: %d value: %d\n", i, *((int *)newVector->data + i));
    }
    printf("Vector number of elements %d\n", newVector->currentNumberOfElements);
    printf("Vector size %d\n", newVector->size);

    removeElementVector_Int(newVector, 3);
    for (int i = 0; i < newVector->currentNumberOfElements; i++)
    {
        printf("Vector: index: %d value: %d\n", i, *((int *)newVector->data + i));
    }
    printf("Vector number of elements %d\n", newVector->currentNumberOfElements);
    printf("Vector size %d\n", newVector->size);

    printf("Element %d found at index %d\n", 2, findElementVector_Int(newVector, 2));
    printf("Element %d found at index %d\n", 3, findElementVector_Int(newVector, 3));

    struct Vector graphVector;
    createVector_Graph(&graphVector, 1);
    pushBackVector_Graph(&graphVector, directedGraph);
    printf("Printing Graph Vector [0]\n");
    printGraph(*(struct Graph *)graphVector.data);
    pushBackVector_Graph(&graphVector, directedGraph);
    printf("Printing Graph Vector [1]\n");
    printGraph(*((struct Graph *)graphVector.data + 1));
}

int main(int argc, char *argv[])
{
    /*
        1. DONE: Read all input graphs from a single file.
        2. DONE: Iterate over them and for each print maximal cliques.
        3. DONE: Multiply all of them and find maximal clique - that will be a maximal common subgraph.
        4. DONE: Instead of printing all the results in BronKerbosch, store them in a pointer and then process it.
        5. DONE: Handle multiple input files.
            1. Iterate over argc - 1.
            2. Modify file loading function to append a vector with graphs.
    */
    clock_t time_begin;
    clock_t time_end;

    clock_t time_all_begin = clock();

    // Initialization
    if (2 > argc)
    {
        printf("Usage: input existing file names separated by space. Example: main.exe file1.txt file2.txt\n");
        return 1;
    }

    // Read graphs from file

    struct Vector graphs;
    createVector_Graph(&graphs, 1);
    int noOfGraphs = 0;
    for (int i = 0; i < argc - 1; i++)
    {
        FILE *filePtr = fopen(argv[i + 1], "rb");

        if (NULL == filePtr)
        {
            printf("Error: could not open file %s", argv[i + 1]);
            return 1;
        }
        readGraphsFromFile(filePtr, &noOfGraphs, &graphs);
        fclose(filePtr);
    }

    if (0 == graphs.currentNumberOfElements)
        return -1;

    FILE *outputFile;

    outputFile = fopen("output.txt", "w");

// Print graphs
#ifdef PRINTTOCMD
    printGraphs(graphs.data, noOfGraphs);
#endif
    time_begin = clock();
#ifdef PRINTTOCMD
    printf("-------------------------------------------------\n");
#endif
    for (int i = 0; i < noOfGraphs; i++)
    {
#ifdef PRINTTOCMD
        printf("-------------------------------------------------\n");
        printf("Maximal cliques for graph %d\n", i);
#endif
        struct Vector R;
        createVector_Int(&R, 1);
        struct Vector P;
        createVector_Int(&P, ((struct Graph *)(graphs.data) + i)->noOfVertices);
#ifdef dbg
        printf("graph size: %d\n", ((struct Graph *)(graphs.data) + i)->noOfVertices);
#endif
        for (int j = 0; j < ((struct Graph *)(graphs.data) + i)->noOfVertices; j++)
        {
            pushBackVector_Int(&P, j);
#ifdef dbg
            printVector_Int(P);
#endif
        }

        struct Vector X;
        createVector_Int(&X, 1);

        struct Vector bronResult;
        createVector_Vector(&bronResult, 1);

        /*
            (I removed the copying of the graph since it doesn't really do anything here. If we would need to somehow retireve the data of the originally removed single edges or edges to self then we need implement a deep copy of a graph in toUndirectedGraph)
            1. toUndirectedGraph actually modifies the graph, because even though it copies the graph it also copies the memory address for the adjacency list, so it just modifies the adjacency list of the original graph.
        */
        toUndirectedGraph(*((struct Graph *)(graphs.data) + i));
        iterBronKerbosch(R, P, X, ((struct Graph *)(graphs.data) + i), &bronResult);
#ifdef PRINTTOCMD
        printVector_Vector(bronResult);
#endif
        fprintf(outputFile, "Maximal Cliques for graph %d: \n", i);
        saveToFileVector_Vector(bronResult, outputFile);

        for (int i = 0; i < bronResult.currentNumberOfElements; i++)
        {
            free(((struct Vector *)bronResult.data + i)->data);
        }
        free(bronResult.data);
        // free(R.data);
        // free(P.data);
        // free(X.data);
    }

    time_end = clock();

    double maximal_cliques_time = (double)(time_end - time_begin) / CLOCKS_PER_SEC;
    double modular_product_time = -1;
    double maximal_clique_modular_product_time = -1;
#ifdef PRINTTOCMD
    printf("-------------------------------------------------\n");
#endif
    // Modular Graph Product

    struct Graph *GH = NULL;
    struct Graph *GH_prev = NULL;

    if (1 < noOfGraphs)
    {
        time_begin = clock();
        GH = graphs.data;
        for (int i = 1; i < noOfGraphs; i++)
        {
            GH = modularProduct(GH, ((struct Graph *)(graphs.data) + i));
            freeGraph(GH_prev);
            free(GH_prev);
            GH_prev = GH;
        }

        time_end = clock();

        modular_product_time = (double)(time_end - time_begin) / CLOCKS_PER_SEC;
        if (NULL != GH)
        {
#ifdef PRINTTOCMD
            printf("-------------------------------------------------\n");
            printf("Modular product graph of all input graphs:\n");
            printGraph(*GH);
#endif
            struct Vector R;
            createVector_Int(&R, 1);
            struct Vector P;
            createVector_Int(&P, 1);
            for (int i = 0; i < GH->noOfVertices; i++)
            {
                pushBackVector_Int(&P, i);
            }
            struct Vector X;
            createVector_Int(&X, 1);

#ifdef PRINTTOCMD
            printf("-------------------------------------------------\n");
            printf("Maximal common subgraphs of all input graphs:\n");
#endif
            struct Vector bronResult;
            createVector_Vector(&bronResult, 1);
            time_begin = clock();
            iterBronKerbosch(R, P, X, GH, &bronResult);
            time_end = clock();

            maximal_clique_modular_product_time = (double)(time_end - time_begin) / CLOCKS_PER_SEC;
#ifdef PRINTTOCMD
            printVector_Vector_Max(bronResult);
#endif
            fprintf(outputFile, "Maximal common induced subgraphs for all input graphs: \n");
            saveToFileVector_Vector_Max(bronResult, outputFile);

            // free(R.data);
            // free((int *)X.data);
            // free(P.data);

            for (int i = 0; i < bronResult.currentNumberOfElements; i++)
            {
                free(((struct Vector *)bronResult.data + i)->data);
            }
            free(bronResult.data);
        }
    }
#ifdef dbg
    dbgTests(*((struct Graph *)(graphs.data)));
#endif // dbg
    clock_t time_all_end = clock();

    printf("Time of calculating maximal cliques (Bron-Kerbosch) for for all input graphs: %fs\n", maximal_cliques_time);
    fprintf(outputFile, "Time of calculating maximal cliques for for all input graphs: %fs\n", maximal_cliques_time);

    printf("Time of calculating modular product for all input graphs: %fs\n", modular_product_time);
    fprintf(outputFile, "Time of calculating modular product for all input graphs: %fs\n", modular_product_time);

    printf("Time of calculating maximal common subgraphs (Bron-Kerbosch) for all input graphs: %fs\n", maximal_clique_modular_product_time);
    fprintf(outputFile, "Time of calculating maximal common subgraphs (Bron-Kerbosch) for all input graphs: %fs\n", maximal_clique_modular_product_time);

    printf("Whole program execution time: %fs\n", (double)(time_all_end - time_all_begin) / CLOCKS_PER_SEC);
    fprintf(outputFile, "Whole program execution time: %fs\n", (double)(time_all_end - time_all_begin) / CLOCKS_PER_SEC);

    freeGraph(GH);
    free(GH);

    for (int i = 0; i < noOfGraphs; i++)
    {
        freeGraph(((struct Graph *)(graphs.data) + i));
    }

    free(((struct Graph *)(graphs.data)));
    fclose(outputFile);
    return 0;
}
