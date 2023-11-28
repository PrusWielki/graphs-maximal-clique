#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <stdint.h>
// #define PRINTTOCMD
// #define dbg

typedef intptr_t ssize_t;

ssize_t getline(char **lineptr, size_t *n, FILE *stream)
{
    size_t pos;
    int c;

    if (lineptr == NULL || stream == NULL || n == NULL)
    {
        errno = EINVAL;
        return -1;
    }

    c = getc(stream);
    if (c == EOF)
    {
        return -1;
    }

    if (*lineptr == NULL)
    {
        *lineptr = malloc(128);
        if (*lineptr == NULL)
        {
            return -1;
        }
        *n = 128;
    }

    pos = 0;
    while (c != EOF)
    {
        if (pos + 1 >= *n)
        {
            size_t new_size = *n + (*n >> 2);
            if (new_size < 128)
            {
                new_size = 128;
            }
            char *new_ptr = realloc(*lineptr, new_size);
            if (new_ptr == NULL)
            {
                return -1;
            }
            *n = new_size;
            *lineptr = new_ptr;
        }

        ((unsigned char *)(*lineptr))[pos++] = c;
        if (c == '\n')
        {
            break;
        }
        c = getc(stream);
    }

    (*lineptr)[pos] = '\0';
    return pos;
}
struct Node
{
    int vertex;
    int weight;
    struct Node *nextNode;
} Node;

struct Graph
{
    int noOfVertices;
    int *adjacencyMatrix;
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
    {
        printf("Error allocating memory for Int Vector");
        exit(EXIT_FAILURE);
    }
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
    {
        printf("Error allocating memory for Graph Vector");
        exit(EXIT_FAILURE);
    }
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
    {
        printf("Error allocating memory for Vector Vector");
        exit(EXIT_FAILURE);
    }
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
        int *newArray = realloc(vector->data, 2 * sizeof(int) * vector->size);
        if (NULL == newArray)
        {
            printf("Error allocating memory when adding new value to int Vector");
            exit(EXIT_FAILURE);
        }
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
        struct Vector *newArray = realloc(vector->data, sizeof(struct Vector) * 2 * vector->size);
        if (NULL == newArray)
        {
            printf("Error allocating memory when adding new value to Vector Vector");
            exit(EXIT_FAILURE);
        }

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
        struct Graph *newArray = realloc(vector->data, sizeof(struct Graph) * 2 * vector->size);
        if (NULL == newArray)
        {
            printf("Error allocating memory when adding new value to Graph Vector");
            exit(EXIT_FAILURE);
        }

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

void printGraph(struct Graph graph)
{

    printf("Amount of vertices: %d\n", graph.noOfVertices);

    for (int i = 0; i < graph.noOfVertices; i++)
    {

        for (int j = 0; j < graph.noOfVertices; j++)
        {
            printf("%d ", graph.adjacencyMatrix[i * graph.noOfVertices + j]);
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

    free(graph->adjacencyMatrix);
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

        newGraph.adjacencyMatrix = calloc(noOfVertices * noOfVertices, sizeof(int));
        if (NULL == newGraph.adjacencyMatrix)
        {
            printf("Error: Couldn't allocate memory for new adjacency lists\n");
            exit(EXIT_FAILURE);
        }

#ifdef dbg
        printf("New adj list[0]: %d\n", newGraph.adjacencyLists[0]);
#endif // dbg
        for (int j = 0; j < noOfVertices; j++)
        {
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
                        newGraph.adjacencyMatrix[j * noOfVertices + k] = weight;
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
                exit(EXIT_FAILURE);
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
                exit(EXIT_FAILURE);
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
        5. DONE: Only potentially: Efficiency perhaps could be improved. When we check if a vertex is not in given adjacency list then also maybe one could check if it's in both instead of doing it separately.
        6. DONE: Handle directed graphs. Edges should be in both directions.
    */
    if (NULL == G || NULL == H || NULL == G->adjacencyMatrix || NULL == H->adjacencyMatrix)
    {
        printf("Error: Couldn't multiply matrices, given matrices don't contain enough information\n");
        return NULL;
    }

    struct Graph *GH = malloc(sizeof(struct Graph));

    if (NULL == GH)
    {
        printf("Error: Couldn't allocate memory for graph product\n");
        exit(EXIT_FAILURE);
    }
    GH->description = malloc(sizeof(char));
    if (NULL == GH->description)
    {
        printf("Error: Couldn't allocate memory for graph product description\n");
        exit(EXIT_FAILURE);
    }
    GH->description[0] = '\0';
    GH->noOfVertices = G->noOfVertices * H->noOfVertices;

    GH->adjacencyMatrix = calloc(GH->noOfVertices * GH->noOfVertices, sizeof(int));

    if (NULL == GH->adjacencyMatrix)
    {
        printf("Error: Couldn't allocate memory for graph product adjacency lists\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < G->noOfVertices; i++) // 1. 2.
    {
        for (int j = 0; j < H->noOfVertices; j++) // 2.1
        {
            for (int k = 0; k < G->noOfVertices; k++) // 4.1.2
            {
                if (k != i && G->adjacencyMatrix[i * G->noOfVertices + k] == 0 && G->adjacencyMatrix[k * G->noOfVertices + i] == 0)
                {
                    for (int l = 0; l < H->noOfVertices; l++)
                    {

                        if (j != l && H->adjacencyMatrix[j * H->noOfVertices + l] == 0 && H->adjacencyMatrix[l * H->noOfVertices + j] == 0)
                        {
                            GH->adjacencyMatrix[(i * H->noOfVertices + j) * GH->noOfVertices + k * H->noOfVertices + l] = 1;
                        }
                    }
                }
                else if (k != i && G->adjacencyMatrix[i * G->noOfVertices + k] != 0 && G->adjacencyMatrix[k * G->noOfVertices + i] != 0)
                {
                    for (int l = 0; l < H->noOfVertices; l++)
                    {

                        if (j != l && H->adjacencyMatrix[j * H->noOfVertices + l] != 0 && H->adjacencyMatrix[l * H->noOfVertices + j] != 0)
                        {
                            GH->adjacencyMatrix[(i * H->noOfVertices + j) * GH->noOfVertices + k * H->noOfVertices + l] = H->adjacencyMatrix[j * H->noOfVertices + l] * H->adjacencyMatrix[l * H->noOfVertices + j];
                        }
                    }
                }
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
        for (int j = 0; j < G.noOfVertices; j++)
        {

            if ((i == j && G.adjacencyMatrix[i * G.noOfVertices + j] != 0) || (G.adjacencyMatrix[i * G.noOfVertices + j] != 0 && G.adjacencyMatrix[j * G.noOfVertices + i] == 0))
            {
                G.adjacencyMatrix[i * G.noOfVertices + j] = 0;
            }
        }
    }
}

int bronKerbosch(struct Vector R, struct Vector P, struct Vector X, struct Graph *graph, struct Vector *bronResult)
{
    /*
        1. DONE: Write a function to transform a directed graph to undirected graph (just remove the single edges)
        2. DONE: Write needed datastructures to hold vertices, I guess we could use a List to dynamically store a list of vertices, or we could implement a vector.
        3. DONE: Write the Bron-Kerbosch
        4. DONE: Test it.
        5. DONE: Free memory, use valgrind :)
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

        for (int i = 0; i < graph->noOfVertices; i++)
        {
            if (graph->adjacencyMatrix[pivot * graph->noOfVertices + i] != 0)
            {
                removeElementVector_Int(&toIterateOver, i);
            }
        }
        while (NULL != iterator)
        {

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
        for (int j = 0; j < P.currentNumberOfElements; j++)
        {
            if (graph->adjacencyMatrix[*((int *)toIterateOver.data + i) * graph->noOfVertices + *((int *)P.data + j)] != 0)

            {
                pushBackVector_Int(&pAndVEdges, *((int *)P.data + j));
            }
        }

        // X ⋂ N(v)
        struct Vector xAndVEdges;
        createVector_Int(&xAndVEdges, X.size);
        for (int j = 0; j < X.currentNumberOfElements; j++)
        {
            if (graph->adjacencyMatrix[*((int *)toIterateOver.data + i) * graph->noOfVertices + *((int *)X.data + j)] != 0)
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
    1. DONE: Test it.
*/
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
        /*
        printVector_Int(currentR);
        printVector_Int(currentP);
        printVector_Int(currentX);
        printf("\n");
                 */

        if (0 == currentP.currentNumberOfElements && 0 == currentX.currentNumberOfElements)
        {
            // printf("Maximal Clique: ");
            // printVector_Int(R);
            // free(currentR.data);
            free(currentX.data);
            free(currentP.data);
            pushBackVector_Vector(bronResult, currentR);
        }

        else
        {
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
                for (int j = 0; j < currentX.currentNumberOfElements; j++)
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
                for (int j = 0; j < currentP.currentNumberOfElements; j++)
                {
                    if (graph->adjacencyMatrix[*((int *)currentP.data) * graph->noOfVertices + *((int *)currentP.data + j)] != 0)
                    {
                        pushBackVector_Int(&pAndVEdges, *((int *)currentP.data + j));
                    }
                }

                struct Vector xAndVEdges;
                createVector_Int(&xAndVEdges, currentX.size);
                for (int j = 0; j < currentX.currentNumberOfElements; j++)
                {
                    if (graph->adjacencyMatrix[*((int *)currentP.data) * graph->noOfVertices + *((int *)currentX.data + j)] != 0)
                    {
                        pushBackVector_Int(&xAndVEdges, *((int *)currentX.data + j));
                    }
                }

                // copy R!!
                struct Vector newR;
                createVector_Int(&newR, currentR.currentNumberOfElements);
                for (int i = 0; i < currentR.currentNumberOfElements; i++)
                {
                    pushBackVector_Int(&newR, *((int *)currentR.data + i));
                }

                pushBackVector_Vector(&stack, newR);
                pushBackVector_Vector(&stack, pNotV);
                pushBackVector_Vector(&stack, xAndV);
                /*
                printf("pushed:\n");
                printVector_Int(newR);printVector_Int(pNotV);
                printVector_Int(xAndV);
                printf("\n");
                        */
                pushBackVector_Vector(&stack, rPlusV);
                pushBackVector_Vector(&stack, pAndVEdges);
                pushBackVector_Vector(&stack, xAndVEdges);
                /*
                printf("pushed:\n");
                printVector_Int(rPlusV);
                printVector_Int(pAndVEdges);
                printVector_Int(xAndVEdges);
                printf("\n");
                             */
            }
            free(currentR.data);
            free(currentX.data);
            free(currentP.data);
        }
    }
    free(stack.data);
    return 0;
}
int iterPivotBronKerbosch(struct Vector R, struct Vector P, struct Vector X, struct Graph *graph, struct Vector *bronResult)
{
    /*
    1. DONE: Test it.
*/

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
        /*
        printVector_Int(currentR);
        printVector_Int(currentP);
        printVector_Int(currentX);
        printf("\n");
                 */

        if (0 == currentP.currentNumberOfElements && 0 == currentX.currentNumberOfElements)
        {
            // printf("Maximal Clique: ");
            // printVector_Int(R);
            // free(currentR.data);
            free(currentX.data);
            free(currentP.data);
            pushBackVector_Vector(bronResult, currentR);
        }

        else
        {
            int pivot = -1;
            if (0 < currentP.currentNumberOfElements)
                pivot = *((int *)currentP.data);

            else if (0 < currentX.currentNumberOfElements)
                pivot = *((int *)currentX.data);

            int q = -1;
            /*
            struct Vector toIterateOver;
            createVector_Int(&toIterateOver, currentP.currentNumberOfElements);
            */
            if (-1 != pivot)
            {

                for (int i = 0; i < currentP.currentNumberOfElements; i++)
                {

                    if (graph->adjacencyMatrix[pivot * graph->noOfVertices + *((int *)currentP.data + i)] == 0)
                    {
                        q = *((int *)currentP.data + i);
                        break;
                    }
                    // pushBackVector_Int(&toIterateOver, *((int *)currentP.data + i));
                }
            }
            /*
            if (-1 != pivot)
            {
                iterator = graph->adjacencyLists[pivot];
                while (NULL != iterator)
                {
                    removeElementVector_Int(&toIterateOver, iterator->vertex);
                    iterator = iterator->nextNode;
                }
            }
 */
            if (-1 != q)
            {

                struct Vector pNotV;
                createVector_Int(&pNotV, currentP.currentNumberOfElements - 1);
                for (int j = 0; j < currentP.currentNumberOfElements; j++)
                {
                    if (*((int *)currentP.data + j) != q)
                        pushBackVector_Int(&pNotV, *((int *)currentP.data + j));
                }
                struct Vector xAndV;
                createVector_Int(&xAndV, currentX.currentNumberOfElements + 1);
                for (int j = 0; j < currentX.currentNumberOfElements; j++)
                {
                    pushBackVector_Int(&xAndV, *((int *)currentX.data + j));
                }
                pushBackVector_Int(&xAndV, q);

                struct Vector rPlusV;
                createVector_Int(&rPlusV, currentR.currentNumberOfElements + 1);
                for (int j = 0; j < currentR.currentNumberOfElements; j++)
                {
                    pushBackVector_Int(&rPlusV, *((int *)currentR.data + j));
                }

                pushBackVector_Int(&rPlusV, q);

                struct Vector pAndVEdges;
                createVector_Int(&pAndVEdges, currentP.size);
                for (int j = 0; j < currentP.currentNumberOfElements; j++)
                {

                    if (graph->adjacencyMatrix[q * graph->noOfVertices + *((int *)currentP.data + j)] != 0)
                    {
                        pushBackVector_Int(&pAndVEdges, *((int *)currentP.data + j));
                    }
                }

                struct Vector xAndVEdges;
                createVector_Int(&xAndVEdges, currentX.size);
                for (int j = 0; j < currentX.currentNumberOfElements; j++)
                {
                    if (graph->adjacencyMatrix[q * graph->noOfVertices + *((int *)currentX.data + j)] != 0)
                    {
                        pushBackVector_Int(&xAndVEdges, *((int *)currentX.data + j));
                    }
                }

                // copy R!!
                struct Vector newR;
                createVector_Int(&newR, currentR.currentNumberOfElements);
                for (int i = 0; i < currentR.currentNumberOfElements; i++)
                {
                    pushBackVector_Int(&newR, *((int *)currentR.data + i));
                }

                pushBackVector_Vector(&stack, newR);
                pushBackVector_Vector(&stack, pNotV);
                pushBackVector_Vector(&stack, xAndV);
                /*
                printf("pushed:\n");
                printVector_Int(newR);printVector_Int(pNotV);
                printVector_Int(xAndV);
                printf("\n");
                        */
                pushBackVector_Vector(&stack, rPlusV);
                pushBackVector_Vector(&stack, pAndVEdges);
                pushBackVector_Vector(&stack, xAndVEdges);
                /*
                printf("pushed:\n");
                printVector_Int(rPlusV);
                printVector_Int(pAndVEdges);
                printVector_Int(xAndVEdges);
                printf("\n");
                             */
            }
            /*    free(toIterateOver.data); */
            free(currentR.data);
            free(currentX.data);
            free(currentP.data);
        }
    }
    free(stack.data);
    return 0;
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
        iterPivotBronKerbosch(R, P, X, ((struct Graph *)(graphs.data) + i), &bronResult);
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
            iterPivotBronKerbosch(R, P, X, GH, &bronResult);
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