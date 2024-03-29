#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <stdint.h>
#define PRINTTOCMD
// #define dbg

#define MAXIMUM_OUTPUT_COUNT 1

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

    for (int i = 0; i < noOfGraphs; i++)
    {
        printf("------------------Graph %d----------------------\n", i);
        printGraph(graphs[i]);
    }
}
int countGraphEdges(struct Graph *graph)
{

    int noOfEdges = 0;
    for (int i = 0; i < graph->noOfVertices; i++)
    {

        for (int j = 0; j < graph->noOfVertices; j++)
        {
            if (graph->adjacencyMatrix[i * graph->noOfVertices + j] != 0)
                noOfEdges = noOfEdges + graph->adjacencyMatrix[i * graph->noOfVertices + j];
        }
    }
    return noOfEdges;
}
void printGraphs_Max(struct Graph *graphs, int noOfGraphs, int limit)
{
    if (0 == limit)
        limit = noOfGraphs;
    int max = graphs[0].noOfVertices + countGraphEdges(graphs);
    for (int i = 1; i < noOfGraphs; i++)
    {
        if (max < graphs[i].noOfVertices + countGraphEdges(graphs + i))
            max = graphs[i].noOfVertices + countGraphEdges(graphs + i);
    }

    int count = 0;

    for (int i = 0; i < noOfGraphs; i++)
    {
        if (0 != limit && count == limit)
            break;
        if (graphs[i].noOfVertices + countGraphEdges(graphs + i) == max)
        {
            if (limit > 1)
                printf("------------------Graph %d----------------------\n", i);

            int noOfEdges = 0;
            noOfEdges = countGraphEdges(graphs + i);
            printf("Graph is of size %d with %d vertices and %d edges\n", noOfEdges + graphs[i].noOfVertices, graphs[i].noOfVertices, noOfEdges);
            printf("Adjacency matrix:\n");
            printGraph(graphs[i]);
            count++;
        }
    }
}
void saveToFileGraph(struct Graph *graph, FILE *output_file)
{
    for (int i = 0; i < graph->noOfVertices; i++)
    {

        for (int j = 0; j < graph->noOfVertices; j++)
        {
            fprintf(output_file, "%d ", graph->adjacencyMatrix[i * graph->noOfVertices + j]);
        }
        fprintf(output_file, "\n");
    }
    fprintf(output_file, "Additional information: %s\n", graph->description);
    fprintf(output_file, "-------------------------------------------------\n\n");
}
void saveToFileGraphs_Max(struct Graph *graphs, FILE *outputFile, int noOfGraphs, int limit)
{
    if (0 == limit)
        limit = noOfGraphs;
    int max = graphs[0].noOfVertices + countGraphEdges(graphs);
    for (int i = 1; i < noOfGraphs; i++)
    {
        int edges = +countGraphEdges(graphs + i);
        if (max < graphs[i].noOfVertices + edges)
            max = graphs[i].noOfVertices + edges;
    }

    int count = 0;

    for (int i = 0; i < noOfGraphs; i++)
    {
        if (0 != limit && count == limit)
            break;
        int noOfEdges = countGraphEdges(graphs + i);
        if (graphs[i].noOfVertices + noOfEdges == max)
        {
            if (limit > 1)
                fprintf(outputFile, "------------------Graph %d----------------------\n", i);

            fprintf(outputFile, "Graph is of size %d with %d vertices and %d edges\n", noOfEdges + graphs[i].noOfVertices, graphs[i].noOfVertices, noOfEdges);
            fprintf(outputFile, "Adjacency matrix:\n");
            saveToFileGraph(graphs + i, outputFile);
            count++;
        }
    }
}

void freeGraph(struct Graph *graph)
{
    if (NULL == graph)
        return;

    graph->noOfVertices = 0;
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
        if (0 == noOfVertices)
        {
            bytesRead = getline(&line, &lineLength, filePtr);

            if (0 >= bytesRead)
            {
                printf("Input file is not in a accepted format\n");
                exit(EXIT_FAILURE);
            }
            noOfVertices = strtol(line, NULL, 10);
        }
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

        int totalDescriptionSize = 0;

        bytesRead = getline(&line, &lineLength, filePtr);
        if (0 < bytesRead && line[0] != '\r' && line[0] != '\n')
        {
            newGraph.description = malloc(sizeof(char) * (bytesRead + 1));
            totalDescriptionSize = bytesRead;
            if (NULL == newGraph.description)
            {

                printf("Error: Couldn't allocate memory for graph description\n");
                exit(EXIT_FAILURE);
            }

            strncpy(newGraph.description, line, bytesRead);

            bytesRead = getline(&line, &lineLength, filePtr);
            while (bytesRead > 0 && line[0] != '\r' && line[0] != '\n')
            {

                char *newDescription = malloc(sizeof(char) * (totalDescriptionSize + bytesRead + 1));

                for (int l = 0; l < totalDescriptionSize; l++)
                {
                    newDescription[l] = newGraph.description[l];
                }
                for (int l = 0; l < bytesRead; l++)
                {
                    newDescription[l + totalDescriptionSize] = line[l];
                }

                totalDescriptionSize = totalDescriptionSize + bytesRead;
                free(newGraph.description);
                newGraph.description = newDescription;
                bytesRead = getline(&line, &lineLength, filePtr);
            }

            // strncpy(newGraph.description, line, bytesRead);
            newGraph.description[totalDescriptionSize] = '\0';
            if (newGraph.description[totalDescriptionSize - 1] == '\n')
                newGraph.description[totalDescriptionSize - 1] = '\0';

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

void maximalCliqueApproximation(struct Graph *graph, struct Vector *result)
{
    // Init sub and rest sets
    struct Vector rest;
    createVector_Int(&rest, 1);
    for (int i = 0; i < graph->noOfVertices; i++)
    {
        pushBackVector_Int(&rest, i);
    }

    while (rest.currentNumberOfElements > 0)
    {
        // Get maximal degree vertex in rest subgraph
        int maxEdges = -1;
        int maxEdgesVertex = -1;
        for (int i = 0; i < graph->noOfVertices; i++)
        {
            int edges = 0;
            if (findElementVector_Int(&rest, i) != -1)
            {
                for (int j = 0; j < graph->noOfVertices; j++)
                {
                    int weight = graph->adjacencyMatrix[graph->noOfVertices * i + j];
                    if (weight > 0 && findElementVector_Int(&rest, j) != -1)
                    {
                        edges++;
                    }
                }
                if (edges > maxEdges)
                {
                    maxEdges = edges;
                    maxEdgesVertex = i;
                }
            }
        }
        pushBackVector_Int(result, maxEdgesVertex);
        removeElementVector_Int(&rest, maxEdgesVertex);
        for (int i = 0; i < graph->noOfVertices; i++)
        {
            if (graph->adjacencyMatrix[graph->noOfVertices * i + maxEdgesVertex] == 0)
            {
                removeElementVector_Int(&rest, i);
            }
        }
    }
    free(rest.data);
}
void retrieveOriginalVertices(struct Vector maximumCommonSubgraph, struct Vector inputGraphs)
{
    /*
        1. Purpose of this function is to map maximum clique from modular graph product to original graphs.
        2. To do that notice that:
            1. In the case of two graphs to retrieve the original vertices one needs to: divide the vertex number from modular graph product
            by the amount of vertices in graph 1, the int result is the index of vertex in 1, then multply the result by the amount of vertices in 1
            and subtract that from the amount of vertices in graph 2 to get the index of vertex from graph 2.
            2. Repeat this process until you get to the first original graph, so repeat n - 1 times, where n is the amount of original graphs.
    */
    struct Vector result;
    createVector_Vector(&result, inputGraphs.currentNumberOfElements);

    for (int i = 0; i < inputGraphs.currentNumberOfElements; i++)
    {
        createVector_Int((struct Vector *)result.data + i, maximumCommonSubgraph.currentNumberOfElements);
    }

    int currentLeftHandGraphSize = ((struct Graph *)inputGraphs.data)->noOfVertices;

    for (int i = 1; i < inputGraphs.currentNumberOfElements - 1; i++)
    {
        currentLeftHandGraphSize = currentLeftHandGraphSize * ((struct Graph *)inputGraphs.data + i)->noOfVertices;
    }

    for (int j = 0; j < maximumCommonSubgraph.currentNumberOfElements; j++)
    {
        int currentVertexIndex = *((int *)maximumCommonSubgraph.data + j);
        int row = currentVertexIndex / ((struct Graph *)inputGraphs.data + inputGraphs.currentNumberOfElements - 1)->noOfVertices;
        for (int i = 0; i < inputGraphs.currentNumberOfElements - 1; i++)
        {

            int column = currentVertexIndex - (row * ((struct Graph *)inputGraphs.data + inputGraphs.currentNumberOfElements - 1 - i)->noOfVertices);
            *((int *)(((struct Vector *)result.data + inputGraphs.currentNumberOfElements - 1 - i)->data) + j) = column;
            ((struct Vector *)result.data + inputGraphs.currentNumberOfElements - 1 - i)->currentNumberOfElements = ((struct Vector *)result.data + inputGraphs.currentNumberOfElements - 1 - i)->currentNumberOfElements + 1;
            if (i < inputGraphs.currentNumberOfElements - 2)
            {
                currentLeftHandGraphSize = currentLeftHandGraphSize / ((struct Graph *)inputGraphs.data + inputGraphs.currentNumberOfElements - 1 - i)->noOfVertices;
                currentVertexIndex = row;
                row = currentVertexIndex / ((struct Graph *)inputGraphs.data + inputGraphs.currentNumberOfElements - 1 - i)->noOfVertices;
            }
        }
        *((int *)(((struct Vector *)result.data)->data) + j) = row;
        ((struct Vector *)result.data)->currentNumberOfElements = ((struct Vector *)result.data)->currentNumberOfElements + 1;
        currentLeftHandGraphSize = ((struct Graph *)inputGraphs.data)->noOfVertices;

        for (int i = 1; i < inputGraphs.currentNumberOfElements - 1; i++)
        {
            currentLeftHandGraphSize = currentLeftHandGraphSize * ((struct Graph *)inputGraphs.data + i)->noOfVertices;
        }
    }
    for (int i = 0; i < inputGraphs.currentNumberOfElements; i++)
    {
        printVector_Int(*((struct Vector *)result.data + i));
        free(((struct Vector *)result.data + i)->data);
    }
    free(result.data);
}

struct Graph retrieveOriginalVerticesGraph(struct Vector maximumCommonSubgraph, struct Vector inputGraphs)
{
    /*
        1. Purpose of this function is to map maximum clique from modular graph product to original graphs.
        2. To do that notice that:
            1. In the case of two graphs to retrieve the original vertices one needs to: divide the vertex number from modular graph product
            by the amount of vertices in graph 1, the int result is the index of vertex in 1, then multply the result by the amount of vertices in 1
            and subtract that from the amount of vertices in graph 2 to get the index of vertex from graph 2.
            2. Repeat this process until you get to the first original graph, so repeat n - 1 times, where n is the amount of original graphs.
    */
    struct Graph toreturn;
    toreturn.noOfVertices = maximumCommonSubgraph.currentNumberOfElements;
    toreturn.adjacencyMatrix = calloc(maximumCommonSubgraph.currentNumberOfElements * maximumCommonSubgraph.currentNumberOfElements, sizeof(int));
    if (NULL == toreturn.adjacencyMatrix)
    {
        printf("Error allocating memory when retrieving original graph");
        exit(EXIT_FAILURE);
    }
    toreturn.description = malloc(sizeof(char));
    if (NULL == toreturn.description)
    {
        printf("Error allocating memory when retrieving original graph");
        exit(EXIT_FAILURE);
    }
    toreturn.description[0] = '\0';
    struct Vector result;
    createVector_Vector(&result, inputGraphs.currentNumberOfElements);

    for (int i = 0; i < inputGraphs.currentNumberOfElements; i++)
    {
        createVector_Int((struct Vector *)result.data + i, maximumCommonSubgraph.currentNumberOfElements);
    }

    int currentLeftHandGraphSize = ((struct Graph *)inputGraphs.data)->noOfVertices;

    for (int i = 1; i < inputGraphs.currentNumberOfElements - 1; i++)
    {
        currentLeftHandGraphSize = currentLeftHandGraphSize * ((struct Graph *)inputGraphs.data + i)->noOfVertices;
    }

    for (int j = 0; j < maximumCommonSubgraph.currentNumberOfElements; j++)
    {
        int currentVertexIndex = *((int *)maximumCommonSubgraph.data + j);
        int row = currentVertexIndex / ((struct Graph *)inputGraphs.data + inputGraphs.currentNumberOfElements - 1)->noOfVertices;
        for (int i = 0; i < inputGraphs.currentNumberOfElements - 1; i++)
        {

            int column = currentVertexIndex - (row * ((struct Graph *)inputGraphs.data + inputGraphs.currentNumberOfElements - 1 - i)->noOfVertices);
            *((int *)(((struct Vector *)result.data + inputGraphs.currentNumberOfElements - 1 - i)->data) + j) = column;
            ((struct Vector *)result.data + inputGraphs.currentNumberOfElements - 1 - i)->currentNumberOfElements = ((struct Vector *)result.data + inputGraphs.currentNumberOfElements - 1 - i)->currentNumberOfElements + 1;
            if (i < inputGraphs.currentNumberOfElements - 2)
            {
                currentLeftHandGraphSize = currentLeftHandGraphSize / ((struct Graph *)inputGraphs.data + inputGraphs.currentNumberOfElements - 1 - i)->noOfVertices;
                currentVertexIndex = row;
                row = currentVertexIndex / ((struct Graph *)inputGraphs.data + inputGraphs.currentNumberOfElements - 1 - i)->noOfVertices;
            }
        }
        *((int *)(((struct Vector *)result.data)->data) + j) = row;
        ((struct Vector *)result.data)->currentNumberOfElements = ((struct Vector *)result.data)->currentNumberOfElements + 1;
        currentLeftHandGraphSize = ((struct Graph *)inputGraphs.data)->noOfVertices;

        for (int i = 1; i < inputGraphs.currentNumberOfElements - 1; i++)
        {
            currentLeftHandGraphSize = currentLeftHandGraphSize * ((struct Graph *)inputGraphs.data + i)->noOfVertices;
        }
    }
    for (int i = 0; i < ((struct Vector *)result.data)->currentNumberOfElements; i++)
    {
        for (int j = 0; j < ((struct Vector *)result.data)->currentNumberOfElements; j++)
        {

            if (((struct Graph *)inputGraphs.data)->adjacencyMatrix[*((int *)(((struct Vector *)result.data)->data) + i) * ((struct Graph *)inputGraphs.data)->noOfVertices + *((int *)(((struct Vector *)result.data)->data) + j)] != 0)
            {

                toreturn.adjacencyMatrix[i * toreturn.noOfVertices + j] = ((struct Graph *)inputGraphs.data)->adjacencyMatrix[*((int *)(((struct Vector *)result.data)->data) + i) * ((struct Graph *)inputGraphs.data)->noOfVertices + *((int *)(((struct Vector *)result.data)->data) + j)];
            }
        }
    }

    // for (int i = 0; i < toreturn.noOfVertices; i++)
    // {
    //     for (int j = 0; j < toreturn.noOfVertices; j++)
    //     {
    //         if (toreturn.adjacencyMatrix[i * toreturn.noOfVertices + j] != 0)
    //         {
    //             toreturn.adjacencyMatrix[j * toreturn.noOfVertices + i] = toreturn.adjacencyMatrix[i * toreturn.noOfVertices + j];
    //         }
    //     }
    // }

    for (int i = 0; i < inputGraphs.currentNumberOfElements; i++)
    {
        // printVector_Int(*((struct Vector *)result.data + i));
        free(((struct Vector *)result.data + i)->data);
    }
    free(result.data);

    return toreturn;
}

struct Graph retrieveOriginalVerticesGraphTwo(struct Vector maximumCommonSubgraph, struct Vector inputGraphs)
{
    /*
        1. Purpose of this function is to map maximum clique from modular graph product to original graphs.
        2. To do that notice that:
            1. In the case of two graphs to retrieve the original vertices one needs to: divide the vertex number from modular graph product
            by the amount of vertices in graph 1, the int result is the index of vertex in 1, then multply the result by the amount of vertices in 1
            and subtract that from the amount of vertices in graph 2 to get the index of vertex from graph 2.
            2. Repeat this process until you get to the first original graph, so repeat n - 1 times, where n is the amount of original graphs.
    */
    struct Graph toreturn;
    toreturn.noOfVertices = maximumCommonSubgraph.currentNumberOfElements;
    toreturn.adjacencyMatrix = calloc(maximumCommonSubgraph.currentNumberOfElements * maximumCommonSubgraph.currentNumberOfElements, sizeof(int));
    if (NULL == toreturn.adjacencyMatrix)
    {
        printf("Error allocating memory when retrieving original graph");
        exit(EXIT_FAILURE);
    }
    toreturn.description = malloc(sizeof(char));
    if (NULL == toreturn.description)
    {
        printf("Error allocating memory when retrieving original graph");
        exit(EXIT_FAILURE);
    }
    toreturn.description[0] = '\0';
    struct Vector result;
    createVector_Vector(&result, inputGraphs.currentNumberOfElements);

    for (int i = 0; i < inputGraphs.currentNumberOfElements; i++)
    {
        createVector_Int((struct Vector *)result.data + i, maximumCommonSubgraph.currentNumberOfElements);
    }

    int currentLeftHandGraphSize = ((struct Graph *)inputGraphs.data)->noOfVertices;

    for (int i = 1; i < inputGraphs.currentNumberOfElements - 1; i++)
    {
        currentLeftHandGraphSize = currentLeftHandGraphSize * ((struct Graph *)inputGraphs.data + i)->noOfVertices;
    }

    for (int j = 0; j < maximumCommonSubgraph.currentNumberOfElements; j++)
    {
        int currentVertexIndex = *((int *)maximumCommonSubgraph.data + j);
        int row = currentVertexIndex / ((struct Graph *)inputGraphs.data + inputGraphs.currentNumberOfElements - 1)->noOfVertices;
        for (int i = 0; i < inputGraphs.currentNumberOfElements - 1; i++)
        {

            int column = currentVertexIndex - (row * ((struct Graph *)inputGraphs.data + inputGraphs.currentNumberOfElements - 1 - i)->noOfVertices);
            *((int *)(((struct Vector *)result.data + inputGraphs.currentNumberOfElements - 1 - i)->data) + j) = column;
            ((struct Vector *)result.data + inputGraphs.currentNumberOfElements - 1 - i)->currentNumberOfElements = ((struct Vector *)result.data + inputGraphs.currentNumberOfElements - 1 - i)->currentNumberOfElements + 1;
            if (i < inputGraphs.currentNumberOfElements - 2)
            {
                currentLeftHandGraphSize = currentLeftHandGraphSize / ((struct Graph *)inputGraphs.data + inputGraphs.currentNumberOfElements - 1 - i)->noOfVertices;
                currentVertexIndex = row;
                row = currentVertexIndex / ((struct Graph *)inputGraphs.data + inputGraphs.currentNumberOfElements - 1 - i)->noOfVertices;
            }
        }
        *((int *)(((struct Vector *)result.data)->data) + j) = row;
        ((struct Vector *)result.data)->currentNumberOfElements = ((struct Vector *)result.data)->currentNumberOfElements + 1;
        currentLeftHandGraphSize = ((struct Graph *)inputGraphs.data)->noOfVertices;

        for (int i = 1; i < inputGraphs.currentNumberOfElements - 1; i++)
        {
            currentLeftHandGraphSize = currentLeftHandGraphSize * ((struct Graph *)inputGraphs.data + i)->noOfVertices;
        }
    }
    for (int i = 0; i < ((struct Vector *)result.data + 1)->currentNumberOfElements; i++)
    {
        for (int j = 0; j < ((struct Vector *)result.data + 1)->currentNumberOfElements; j++)
        {

            if (((struct Graph *)inputGraphs.data + 1)->adjacencyMatrix[*((int *)(((struct Vector *)result.data + 1)->data) + i) * ((struct Graph *)inputGraphs.data + 1)->noOfVertices + *((int *)(((struct Vector *)result.data + 1)->data) + j)] != 0)
            {

                toreturn.adjacencyMatrix[i * toreturn.noOfVertices + j] = ((struct Graph *)inputGraphs.data + 1)->adjacencyMatrix[*((int *)(((struct Vector *)result.data + 1)->data) + i) * ((struct Graph *)inputGraphs.data + 1)->noOfVertices + *((int *)(((struct Vector *)result.data + 1)->data) + j)];
            }
        }
    }

    // for (int i = 0; i < toreturn.noOfVertices; i++)
    // {
    //     for (int j = 0; j < toreturn.noOfVertices; j++)
    //     {
    //         if (toreturn.adjacencyMatrix[i * toreturn.noOfVertices + j] != 0)
    //         {
    //             toreturn.adjacencyMatrix[j * toreturn.noOfVertices + i] = toreturn.adjacencyMatrix[i * toreturn.noOfVertices + j];
    //         }
    //     }
    // }

    for (int i = 0; i < inputGraphs.currentNumberOfElements; i++)
    {
        // printVector_Int(*((struct Vector *)result.data + i));
        free(((struct Vector *)result.data + i)->data);
    }
    free(result.data);

    return toreturn;
}
int getFactorial(int n)
{
    if (n < 1)
        return -1;
    int result = 1;
    for (int i = 1; i < n; i++)
    {
        result = result * i;
    }
    return result;
}
int isASubgraph(struct Vector maximumCommonSubgraph, struct Graph originalGraph1, struct Graph originalGraph2)
{

    /*
        1. Take a found maximum common subgraph candidate and second graph of multiplication.
        2. Permute the found maximum common subgraph candidate, I think it might simply mean changing the order of rows in adjacency matrix maybe, maybe it should be done with respect to diagonal.
            1. To permutate one needs to swap rows AND columns.
            2. Generate pairs of numbers, all from a given range, were order does not matter.
        3. Wrong I think: For each permutation find a maximum common subgraph of the candidate and the second graph.
        3. Map the result to the second graph.
        3. For each permutation
            1. Compare the permutated result with the mapped result
    */
    if (maximumCommonSubgraph.currentNumberOfElements <= 1)
        return 1;
    struct Vector inputGraphs;
    createVector_Graph(&inputGraphs, 2);
    pushBackVector_Graph(&inputGraphs, originalGraph1);
    pushBackVector_Graph(&inputGraphs, originalGraph2);
    struct Graph mapped2 = retrieveOriginalVerticesGraphTwo(maximumCommonSubgraph, inputGraphs);
    struct Graph mapped1 = retrieveOriginalVerticesGraph(maximumCommonSubgraph, inputGraphs);
    int noOfPermutations = getFactorial(mapped2.noOfVertices);

    struct Vector permutations;
    createVector_Vector(&permutations, noOfPermutations);
    for (int i = 0; i < mapped2.noOfVertices; i++)
    {

        for (int j = i + 1; j < mapped2.noOfVertices; j++)
        {
            struct Vector toPush;
            createVector_Int(&toPush, 2);
            pushBackVector_Int(&toPush, i);
            pushBackVector_Int(&toPush, j);
            pushBackVector_Vector(&permutations, toPush);
        }
    }
    // For each permutation create a new graph and test it

    for (int i = 0; i < permutations.currentNumberOfElements; i++)
    {

        struct Graph permutatedMappedGraph;
        permutatedMappedGraph.noOfVertices = mapped2.noOfVertices;

        permutatedMappedGraph.adjacencyMatrix = calloc(mapped2.noOfVertices * mapped2.noOfVertices, sizeof(int));
        if (NULL == permutatedMappedGraph.adjacencyMatrix)
        {
            printf("Couldn't allocate memory to push a found maximum common subgraph\n");
            exit(EXIT_FAILURE);
        }
        permutatedMappedGraph.description = malloc(sizeof(char));
        if (NULL == permutatedMappedGraph.description)
        {
            printf("Couldn't allocate memory to push a found maximum common subgraph\n");
            exit(EXIT_FAILURE);
        }
        permutatedMappedGraph.description[0] = '\0';

        for (int j = 0; j < permutatedMappedGraph.noOfVertices; j++)
        {
            for (int k = 0; k < permutatedMappedGraph.noOfVertices; k++)
            {
                int row = j;
                int column = k;
                if ((row == *(int *)((struct Vector *)permutations.data + i)->data && column == *((int *)(((struct Vector *)permutations.data + i)->data) + 1)) || (column == *(int *)((struct Vector *)permutations.data + i)->data && row == *((int *)(((struct Vector *)permutations.data + i)->data) + 1)))
                {
                    row = k;
                    column = j;
                }
                permutatedMappedGraph.adjacencyMatrix[row * permutatedMappedGraph.noOfVertices + column] = mapped1.adjacencyMatrix[j * mapped1.noOfVertices + k];
            }
        }
        int theSame = 1;
        for (int j = 0; j < permutatedMappedGraph.noOfVertices; j++)
        {
            for (int k = 0; k < permutatedMappedGraph.noOfVertices; k++)
            {
                if (permutatedMappedGraph.adjacencyMatrix[j * permutatedMappedGraph.noOfVertices + k] != mapped2.adjacencyMatrix[j * mapped2.noOfVertices + k])
                {
                    theSame = -1;
                    break;
                }
            }
            if (-1 == theSame)
                break;
        }
        if (-1 != theSame)
        {
            for (int i = 0; i < permutations.currentNumberOfElements; i++)
            {
                free(((struct Vector *)permutations.data + i)->data);
            }
            free(permutations.data);
            freeGraph(&mapped1);
            freeGraph(&mapped2);
            free(inputGraphs.data);
            freeGraph(&permutatedMappedGraph);
            return 1;
        }

        freeGraph(&permutatedMappedGraph);
    }

    for (int i = 0; i < permutations.currentNumberOfElements; i++)
    {
        free(((struct Vector *)permutations.data + i)->data);
    }
    free(permutations.data);

    freeGraph(&mapped1);
    freeGraph(&mapped2);
    free(inputGraphs.data);

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
    double maximal_cliques_time = -1;
    double maximal_clique_approximation_time = -1;
    // double modular_product_time = -1;
    double maximal_clique_modular_product_time = -1;
    double maximal_common_subgraph_approximation_time = -1;

    clock_t time_all_begin = clock();

    // Initialization
    if (2 > argc)
    {
        printf("Usage: input existing file names separated by space. Example: main.exe file1.txt file2.txt\n");
        return 1;
    }

    // -------------------------------------------------------------------------------------------------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------------------------------------------
    // ----------------------------------------------------Read From File-------------------------------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------------------------------------------

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

    // -------------------------------------------------------------------------------------------------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------------------------------------------
    // ----------------------------------------------------Save and print read graphs-------------------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------------------------------------------

    int noOfEdges = 0;
    for (int i = 0; i < graphs.currentNumberOfElements; i++)
    {
        noOfEdges = countGraphEdges(((struct Graph *)(graphs.data) + i));
        fprintf(outputFile, "------------------Graph %d----------------------\n", i);
        fprintf(outputFile, "Graph is of size %d with %d vertices and %d edges\n", noOfEdges + ((struct Graph *)(graphs.data) + i)->noOfVertices, ((struct Graph *)(graphs.data) + i)->noOfVertices, noOfEdges);
        fprintf(outputFile, "Adjacency matrix:\n");
        saveToFileGraph(((struct Graph *)(graphs.data) + i), outputFile);
    }
// Print graphs
#ifdef PRINTTOCMD
    printGraphs(graphs.data, noOfGraphs);
#endif

    // -------------------------------------------------------------------------------------------------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------------------------------------------
    // ----------------------------------------------------Maximum Cliques Exact------------------------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------------------------------------------

    time_begin = clock();
    for (int i = 0; i < noOfGraphs; i++)
    {
#ifdef PRINTTOCMD
        printf("Maximum cliques for graph %d\n", i);
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
        printVector_Vector_Max(bronResult);
#endif
        fprintf(outputFile, "Maximum Cliques for graph %d: \n", i);
        saveToFileVector_Vector_Max(bronResult, outputFile);

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
    maximal_cliques_time = (double)(time_end - time_begin) / CLOCKS_PER_SEC;

    // -------------------------------------------------------------------------------------------------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------------------------------------------
    // ----------------------------------------------------Maximum Cliques Approximation----------------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------------------------------------------
    struct Vector approximationResult;
    createVector_Vector(&approximationResult, noOfGraphs);
    time_begin = clock();
    for (int i = 0; i < noOfGraphs; i++)
    {
        struct Vector approximation;
        createVector_Int(&approximation, 1);
        pushBackVector_Vector(&approximationResult, approximation);
        maximalCliqueApproximation((struct Graph *)graphs.data + i, (struct Vector *)approximationResult.data + i);
    }
    time_end = clock();
    maximal_clique_approximation_time = (double)(time_end - time_begin) / CLOCKS_PER_SEC;

    for (int i = 0; i < noOfGraphs; i++)
    {
        struct Vector currentResult = *((struct Vector *)approximationResult.data + i);
#ifdef PRINTTOCMD
        printf("Maximum clique approximation for graph %d\n", i);
        printVector_Int(currentResult);
        // printVector_Vector(approximationResult);
#endif

        fprintf(outputFile, "Maximum Clique approximation for graph %d: \n", i);
        fprintf(outputFile, "[ ");
        for (int j = 0; j < currentResult.currentNumberOfElements; j++)
        {
            fprintf(outputFile, "%d ", *((int *)currentResult.data + j));
        }

        fprintf(outputFile, "]\n");
    }

    for (int i = 0; i < approximationResult.currentNumberOfElements; i++)
    {
        free(((struct Vector *)approximationResult.data + i)->data);
    }
    free(approximationResult.data);

    // -------------------------------------------------------------------------------------------------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------------------------------------------
    // ----------------------------------------------------Maximum Common Subgraph Exact----------------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------------------------------------------

    struct Graph *GH = NULL;

    if (1 < noOfGraphs)
    {
        /*
            1. Abstract
            DONE: To add backtracking:
            1. Instead of taking just the first largest bronResult, take all the max results.
            2. For each max result do the process.
            3. Repeat.
            4. Can do this with recursion of a stack.
                1. a stack is an array of arrays of maxbron result for each branch of computation. Also should probably store the depth of computation for each array.
                2. The stack should hold: array of maximum common cliques, two graphs that resulted in the maximum common clique, next graph to multiply with, if next graph is null we are at a leaf.
            3. Procedure:
                1. Initialize the stack with two graphs, maximum common subgraphs of those graphs, and next graph if more than 2 graphs, else null, and index of the furthest of two graphs.
                2. If stack is not empty do:
                    1. For each stack element:
                        1. Take one of the maximum cliques, so the below for each maximum clique in the set. Pop the vector and loop over it.
                        2. Map it onto the original graphs present in stack.
                        3. If there is a next graph (should also hold index of the current graph in stack):
                            1. Multiply the result by the next graph.
                            2. Find the maximum cliques of the multiplication.
                            3. Push to stack: new maximum cliques, taken maximum clique mapped onto one of the graphs, next graph that was multipled, next graph.
                        4. Else:
                            1. Push the original graph to results.
                3. Take the results and report largest results as maximum common subgraph.
            4. DONE: Free Memory
            5. DONE: Check for isomorphism.
                1. I think it's enough that after we find the mapped maximum clique, we check if it's isomorphic to both original graphs, if not dont push to stack.
            6. OPTIONAL: Actually I don't think it's worth doing, I don't copy graphs, just the pointers so it won't give us much space or time: Optimize graph copying, stack doesnt have to contain the second modular product graph I think, just index should be enough and the originalGraph

        */

        // stack
        struct Vector stackMaximumClique;
        createVector_Vector(&stackMaximumClique, 1);
        // Hold vectors of size 2, that hold original graphs.
        struct Vector stackOriginalGraphs;
        createVector_Vector(&stackOriginalGraphs, 1);

        // struct Vector stackNextGraph;
        // createVector_Graph(&stackNextGraph, 1);

        struct Vector stackCurrentIndex;
        createVector_Int(&stackCurrentIndex, 1);

        struct Vector finalResults;

        createVector_Graph(&finalResults, 1);

        maximal_clique_modular_product_time = 0;
        time_begin = clock();
        struct Vector toRetrieveGraphs;
        createVector_Graph(&toRetrieveGraphs, 2);
        *((struct Graph *)(toRetrieveGraphs.data)) = *(struct Graph *)graphs.data;
        *((struct Graph *)(toRetrieveGraphs.data) + 1) = *((struct Graph *)graphs.data + 1);
        toRetrieveGraphs.currentNumberOfElements = 2;
        GH = modularProduct(((struct Graph *)(graphs.data)), ((struct Graph *)(graphs.data) + 1));

        struct Vector R;
        createVector_Int(&R, 1);
        struct Vector P;
        createVector_Int(&P, 1);
        for (int j = 0; j < GH->noOfVertices; j++)
        {
            pushBackVector_Int(&P, j);
        }
        struct Vector X;
        createVector_Int(&X, 1);

        struct Vector bronResult;
        createVector_Vector(&bronResult, 1);
        iterPivotBronKerbosch(R, P, X, GH, &bronResult);

        struct Vector maxBrons;

        createVector_Vector(&maxBrons, 1);

        // int max = 0;
        // for (int i = 0; i < bronResult.currentNumberOfElements; i++)
        // {

        //     if (max < ((struct Vector *)(bronResult.data) + i)->currentNumberOfElements)
        //     {
        //         max = ((struct Vector *)(bronResult.data) + i)->currentNumberOfElements;
        //     }
        // }
        for (int i = 0; i < bronResult.currentNumberOfElements; i++)
        {

            // if (max == ((struct Vector *)(bronResult.data) + i)->currentNumberOfElements)
            // {
            struct Vector toPush;
            createVector_Int(&toPush, 1);
            for (int j = 0; j < ((struct Vector *)(bronResult.data) + i)->currentNumberOfElements; j++)
            {
                pushBackVector_Int(&toPush, *((int *)(((struct Vector *)(bronResult.data) + i)->data) + j));
            }
            pushBackVector_Vector(&maxBrons, toPush);
            // }
        }

        // 3.1
        pushBackVector_Vector(&stackOriginalGraphs, toRetrieveGraphs);
        pushBackVector_Vector(&stackMaximumClique, maxBrons);
        pushBackVector_Int(&stackCurrentIndex, 1);
        // if (noOfGraphs > 2)
        // {
        //     pushBackVector_Graph(&stackNextGraph, *((struct Graph *)(graphs.data) + 2));
        // }
        // else
        // {
        //     struct Graph emptyGraph;
        //     emptyGraph.noOfVertices = 0;
        //     pushBackVector_Graph(&stackNextGraph, emptyGraph);
        // }

        struct Graph originalSubgraph;
        originalSubgraph.adjacencyMatrix = NULL;
        originalSubgraph.description = NULL;
        struct Graph newOriginalSubgraph;
        newOriginalSubgraph.adjacencyMatrix = NULL;
        newOriginalSubgraph.description = NULL;

        // OPTIONAL: Don't take all cliques at once, take the nth maximum and loop instead, stop when nth maximum cannot be found, main loop should repeat for the amount of maximums in the main bron result.
        //

        // 3.2
        int mainLoopIndex = 0;
        while (stackMaximumClique.currentNumberOfElements > 0)
        {
            // 3.2.1.1
            struct Vector currentMaximumCliques = popVector_Vector(&stackMaximumClique);

            // Filter the currentMaximumCliques to be the length of at least max of current finalResult
            if (finalResults.currentNumberOfElements > 0)
            {
                int max = ((struct Graph *)finalResults.data)->noOfVertices;

                for (int o = 0; o < finalResults.currentNumberOfElements; o++)
                {
                    if (max < ((struct Graph *)finalResults.data + o)->noOfVertices)
                    {
                        max = ((struct Graph *)finalResults.data + o)->noOfVertices;
                    }
                }

                // filter

                int o = 0;
                while (o < currentMaximumCliques.currentNumberOfElements)
                {

                    if (max >= ((struct Vector *)currentMaximumCliques.data + o)->currentNumberOfElements)
                    {
                        free(((struct Vector *)currentMaximumCliques.data + o)->data);
                        for (int n = o; n < currentMaximumCliques.currentNumberOfElements - 1; n++)
                        {

                            *((struct Vector *)currentMaximumCliques.data + n) = *((struct Vector *)currentMaximumCliques.data + n + 1);
                        }
                        currentMaximumCliques.currentNumberOfElements = currentMaximumCliques.currentNumberOfElements - 1;
                    }
                    else
                        o++;
                }
            }
            toRetrieveGraphs = popVector_Vector(&stackOriginalGraphs);
            int index = *((int *)(stackCurrentIndex.data) + stackCurrentIndex.currentNumberOfElements - 1);
            stackCurrentIndex.currentNumberOfElements = stackCurrentIndex.currentNumberOfElements - 1;
            for (int k = 0; k < currentMaximumCliques.currentNumberOfElements; k++)
            {
                // 3.2.1.2

                if (0 == isASubgraph(*((struct Vector *)(currentMaximumCliques.data) + k), *(struct Graph *)toRetrieveGraphs.data, *((struct Graph *)toRetrieveGraphs.data + 1)))
                    continue;
                if (finalResults.currentNumberOfElements > 0 && ((struct Vector *)(currentMaximumCliques.data) + k)->currentNumberOfElements <= ((struct Graph *)finalResults.data)->noOfVertices)
                    continue;

                originalSubgraph = retrieveOriginalVerticesGraph(*((struct Vector *)(currentMaximumCliques.data) + k), toRetrieveGraphs);

                // 3.2.1.3

                if (index < noOfGraphs - 1)
                {
                    // 3.2.1.3.1
                    freeGraph(GH);
                    free(GH);
                    GH = modularProduct(&originalSubgraph, ((struct Graph *)(graphs.data) + index + 1));

                    // 3.2.1.3.2

                    struct Vector R;
                    createVector_Int(&R, 1);
                    struct Vector P;
                    createVector_Int(&P, 1);
                    for (int j = 0; j < GH->noOfVertices; j++)
                    {
                        pushBackVector_Int(&P, j);
                    }
                    struct Vector X;
                    createVector_Int(&X, 1);

                    struct Vector bronResult;
                    createVector_Vector(&bronResult, 1);
                    iterPivotBronKerbosch(R, P, X, GH, &bronResult);

                    struct Vector maxBrons;

                    createVector_Vector(&maxBrons, 1);

                    // int max = 0;
                    // for (int i = 0; i < bronResult.currentNumberOfElements; i++)
                    // {

                    //     if (max < ((struct Vector *)(bronResult.data) + i)->currentNumberOfElements)
                    //     {
                    //         max = ((struct Vector *)(bronResult.data) + i)->currentNumberOfElements;
                    //     }
                    // }
                    for (int i = 0; i < bronResult.currentNumberOfElements; i++)
                    {

                        // if (max == ((struct Vector *)(bronResult.data) + i)->currentNumberOfElements)
                        // {
                        struct Vector toPush;
                        createVector_Int(&toPush, 1);
                        for (int j = 0; j < ((struct Vector *)(bronResult.data) + i)->currentNumberOfElements; j++)
                        {
                            pushBackVector_Int(&toPush, *((int *)(((struct Vector *)(bronResult.data) + i)->data) + j));
                        }
                        pushBackVector_Vector(&maxBrons, toPush);
                        // }
                    }
                    for (int i = 0; i < bronResult.currentNumberOfElements; i++)
                    {
                        free(((struct Vector *)bronResult.data + i)->data);
                    }
                    free(bronResult.data);

                    // 3.2.1.3.3

                    pushBackVector_Vector(&stackMaximumClique, maxBrons);

                    struct Vector newToRetrieveGraphs;
                    createVector_Graph(&newToRetrieveGraphs, 2);
                    struct Graph graphToPush;
                    graphToPush.noOfVertices = originalSubgraph.noOfVertices;
                    graphToPush.adjacencyMatrix = calloc(originalSubgraph.noOfVertices * originalSubgraph.noOfVertices, sizeof(int));
                    if (NULL == graphToPush.adjacencyMatrix)
                    {
                        printf("Couldn't allocate memory to push a found maximum common subgraph\n");
                        exit(EXIT_FAILURE);
                    }
                    graphToPush.description = malloc(sizeof(char));
                    if (NULL == graphToPush.description)
                    {
                        printf("Couldn't allocate memory to push a found maximum common subgraph\n");
                        exit(EXIT_FAILURE);
                    }
                    graphToPush.description[0] = '\0';
                    for (int l = 0; l < originalSubgraph.noOfVertices; l++)
                    {
                        for (int m = 0; m < originalSubgraph.noOfVertices; m++)
                        {

                            graphToPush.adjacencyMatrix[l * graphToPush.noOfVertices + m] = originalSubgraph.adjacencyMatrix[l * originalSubgraph.noOfVertices + m];
                        }
                    }
                    *((struct Graph *)(newToRetrieveGraphs.data)) = graphToPush;
                    freeGraph(&originalSubgraph);
                    *((struct Graph *)(newToRetrieveGraphs.data) + 1) = *((struct Graph *)graphs.data + index + 1);
                    newToRetrieveGraphs.currentNumberOfElements = 2;
                    pushBackVector_Vector(&stackOriginalGraphs, newToRetrieveGraphs);

                    pushBackVector_Int(&stackCurrentIndex, index + 1);
                }
                else
                {
                    struct Graph graphToPush;
                    graphToPush.noOfVertices = originalSubgraph.noOfVertices;
                    graphToPush.adjacencyMatrix = calloc(originalSubgraph.noOfVertices * originalSubgraph.noOfVertices, sizeof(int));
                    if (NULL == graphToPush.adjacencyMatrix)
                    {
                        printf("Couldn't allocate memory to push a found maximum common subgraph\n");
                        exit(EXIT_FAILURE);
                    }
                    graphToPush.description = malloc(sizeof(char));
                    if (NULL == graphToPush.description)
                    {
                        printf("Couldn't allocate memory to push a found maximum common subgraph\n");
                        exit(EXIT_FAILURE);
                    }
                    graphToPush.description[0] = '\0';
                    for (int l = 0; l < originalSubgraph.noOfVertices; l++)
                    {
                        for (int m = 0; m < originalSubgraph.noOfVertices; m++)
                        {

                            graphToPush.adjacencyMatrix[l * graphToPush.noOfVertices + m] = originalSubgraph.adjacencyMatrix[l * originalSubgraph.noOfVertices + m];
                        }
                    }
                    freeGraph(&originalSubgraph);
                    if (finalResults.currentNumberOfElements > 0)
                        freeGraph(finalResults.data);
                    finalResults.currentNumberOfElements = 1;

                    *(struct Graph *)finalResults.data = graphToPush;
                    // printGraph(graphToPush);
                    // pushBackVector_Graph(&finalResults, graphToPush);
                }
            }
            for (int m = 0; m < currentMaximumCliques.currentNumberOfElements; m++)
            {
                free(((struct Vector *)currentMaximumCliques.data + m)->data);
            }
            free(currentMaximumCliques.data);
            if (mainLoopIndex != 0)
                freeGraph(toRetrieveGraphs.data);
            free(toRetrieveGraphs.data);
            mainLoopIndex++;
        }
        free(stackCurrentIndex.data);
        free(stackMaximumClique.data);
        free(stackOriginalGraphs.data);
        if (stackOriginalGraphs.currentNumberOfElements > 0)
            freeGraph(((struct Vector *)stackOriginalGraphs.data)->data);
        fprintf(outputFile, "\n-------------------------------------------------\n");
        fprintf(outputFile, "Maximum common subgraph for all input graphs: \n");
#ifdef PRINTTOCMD
        printf("\n-------------------------------------------------\n");
        printf("Maximum common subgraph for all input graphs: \n");
#endif

#ifdef PRINTTOCMD
        if (finalResults.data != NULL && finalResults.currentNumberOfElements > 0)
            printGraphs_Max((struct Graph *)finalResults.data, finalResults.currentNumberOfElements, MAXIMUM_OUTPUT_COUNT);
#endif
        if (finalResults.data != NULL && finalResults.currentNumberOfElements > 0)
            saveToFileGraphs_Max((struct Graph *)finalResults.data, outputFile, finalResults.currentNumberOfElements, MAXIMUM_OUTPUT_COUNT);

        for (int i = 0; i < finalResults.currentNumberOfElements; i++)
        {
            freeGraph((struct Graph *)finalResults.data + i);
        }
        free(finalResults.data);

        freeGraph(&newOriginalSubgraph);
        // freeGraph(&originalSubgraph);
        for (int i = 0; i < bronResult.currentNumberOfElements; i++)
        {
            free(((struct Vector *)bronResult.data + i)->data);
        }
        free(bronResult.data);

        time_end = clock();
        maximal_clique_modular_product_time = (double)(time_end - time_begin) / CLOCKS_PER_SEC;

        // -------------------------------------------------------------------------------------------------------------------------------------------------
        // -------------------------------------------------------------------------------------------------------------------------------------------------
        // ----------------------------------------------------Maximum Common Subgraph Approximation--------------------------------------------------------
        // -------------------------------------------------------------------------------------------------------------------------------------------------
        // -------------------------------------------------------------------------------------------------------------------------------------------------

        time_begin = clock();

        createVector_Graph(&toRetrieveGraphs, 2);
        *((struct Graph *)(toRetrieveGraphs.data)) = *(struct Graph *)graphs.data;
        *((struct Graph *)(toRetrieveGraphs.data) + 1) = *((struct Graph *)graphs.data + 1);
        toRetrieveGraphs.currentNumberOfElements = 2;
        freeGraph(GH);
        free(GH);
        GH = modularProduct(((struct Graph *)(graphs.data)), ((struct Graph *)(graphs.data) + 1));

        originalSubgraph.adjacencyMatrix = NULL;
        originalSubgraph.description = NULL;
        originalSubgraph.noOfVertices = 0;
        newOriginalSubgraph.adjacencyMatrix = NULL;
        newOriginalSubgraph.description = NULL;
        newOriginalSubgraph.noOfVertices = 0;
        struct Vector modularProductApproximationResult;
        modularProductApproximationResult.data = NULL;
        for (int i = 2; i < noOfGraphs; i++)
        {
            free(modularProductApproximationResult.data);

            createVector_Int(&modularProductApproximationResult, GH->noOfVertices);

            maximalCliqueApproximation(GH, &modularProductApproximationResult);

            freeGraph(&newOriginalSubgraph);

            if (0 == isASubgraph(modularProductApproximationResult, *(struct Graph *)toRetrieveGraphs.data, *((struct Graph *)toRetrieveGraphs.data + 1)))
                break;

            newOriginalSubgraph = retrieveOriginalVerticesGraph(modularProductApproximationResult, toRetrieveGraphs);
            freeGraph(&originalSubgraph);
            originalSubgraph.adjacencyMatrix = calloc(newOriginalSubgraph.noOfVertices * newOriginalSubgraph.noOfVertices, sizeof(int));

            if (NULL == originalSubgraph.adjacencyMatrix)
            {

                printf("Couldn't allocate memory for new subgraph in main\n");
                exit(EXIT_FAILURE);
            }
            originalSubgraph.noOfVertices = newOriginalSubgraph.noOfVertices;
            for (int j = 0; j < newOriginalSubgraph.noOfVertices; j++)
            {

                for (int k = 0; k < newOriginalSubgraph.noOfVertices; k++)
                {
                    originalSubgraph.adjacencyMatrix[j * newOriginalSubgraph.noOfVertices + k] = newOriginalSubgraph.adjacencyMatrix[j * newOriginalSubgraph.noOfVertices + k];
                }
            }
            originalSubgraph.description = malloc(sizeof(char));
            if (NULL == originalSubgraph.description)
            {

                printf("Couldn't allocate memory for new subgraph in main\n");
                exit(EXIT_FAILURE);
            }
            originalSubgraph.description[0] = '\0';
            // printGraph(originalSubgraph);
            freeGraph(GH);
            free(GH);
            GH = modularProduct(&originalSubgraph, ((struct Graph *)(graphs.data) + i));

            *((struct Graph *)(toRetrieveGraphs.data)) = originalSubgraph;
            *((struct Graph *)(toRetrieveGraphs.data) + 1) = *((struct Graph *)(graphs.data) + i);
        }

        free(modularProductApproximationResult.data);
        createVector_Int(&modularProductApproximationResult, GH->noOfVertices);
        maximalCliqueApproximation(GH, &modularProductApproximationResult);

        freeGraph(&newOriginalSubgraph);

        if (0 != isASubgraph(modularProductApproximationResult, *(struct Graph *)toRetrieveGraphs.data, *((struct Graph *)toRetrieveGraphs.data + 1)))
        {
            newOriginalSubgraph = retrieveOriginalVerticesGraph(modularProductApproximationResult, toRetrieveGraphs);

            freeGraph(&originalSubgraph);
            originalSubgraph.adjacencyMatrix = calloc(newOriginalSubgraph.noOfVertices * newOriginalSubgraph.noOfVertices, sizeof(int));

            if (NULL == originalSubgraph.adjacencyMatrix)
            {

                printf("Couldn't allocate memory for new subgraph in main\n");
                exit(EXIT_FAILURE);
            }
            originalSubgraph.noOfVertices = newOriginalSubgraph.noOfVertices;
            for (int j = 0; j < newOriginalSubgraph.noOfVertices; j++)
            {

                for (int k = 0; k < newOriginalSubgraph.noOfVertices; k++)
                {
                    originalSubgraph.adjacencyMatrix[j * newOriginalSubgraph.noOfVertices + k] = newOriginalSubgraph.adjacencyMatrix[j * newOriginalSubgraph.noOfVertices + k];
                }
            }
            originalSubgraph.description = malloc(sizeof(char));
            if (NULL == originalSubgraph.description)
            {

                printf("Couldn't allocate memory for new subgraph in main\n");
                exit(EXIT_FAILURE);
            }
            originalSubgraph.description[0] = '\0';
        }
        else
        {
            freeGraph(&originalSubgraph);
        }

        fprintf(outputFile, "-------------------------------------------------\n");
        fprintf(outputFile, "Maximum common subgraph approximation for all input graphs: \n");
#ifdef PRINTTOCMD
        printf("-------------------------------------------------\n");
        printf("Maximum common subgraph approximation for all input graphs: \n");
#endif
        if (originalSubgraph.noOfVertices > 0)
        {
            noOfEdges = 0;
            noOfEdges = countGraphEdges(&originalSubgraph);
            fprintf(outputFile, "Graph is of size %d with %d vertices and %d edges\n", noOfEdges + originalSubgraph.noOfVertices, originalSubgraph.noOfVertices, noOfEdges);
            fprintf(outputFile, "Adjacency matrix:\n");
#ifdef PRINTTOCMD
            printf("Graph is of size %d with %d vertices and %d edges\n", noOfEdges + originalSubgraph.noOfVertices, originalSubgraph.noOfVertices, noOfEdges);
            printf("Adjacency matrix:\n");
            printGraph(originalSubgraph);

#endif
            saveToFileGraph(&originalSubgraph, outputFile);
            freeGraph(&newOriginalSubgraph);
            freeGraph(&originalSubgraph);

            free(toRetrieveGraphs.data);
            free(modularProductApproximationResult.data);
            time_end = clock();
            maximal_common_subgraph_approximation_time = (double)(time_end - time_begin) / CLOCKS_PER_SEC;
        }
        else
        {

            printf("Could not find Maximum Common Subgraph Approximation in polynomial time (exact solution might still exist)\n");
            fprintf(outputFile, "Could not find Maximum Common Subgraph Approximation in polynomial time (exact solution might still exist)\n");
            if (newOriginalSubgraph.noOfVertices > 0)
                freeGraph(&newOriginalSubgraph);
            if (originalSubgraph.noOfVertices > 0)
                freeGraph(&originalSubgraph);

            free(toRetrieveGraphs.data);
            free(modularProductApproximationResult.data);
        }
    }
#ifdef dbg
    dbgTests(*((struct Graph *)(graphs.data)));
#endif // dbg
    clock_t time_all_end = clock();

    printf("Time of calculating maximum cliques (Bron-Kerbosch) for for all input graphs: %fs\n", maximal_cliques_time);
    fprintf(outputFile, "Time of calculating maximum cliques (Bron-Kerbosch) for for all input graphs: %fs\n", maximal_cliques_time);

    printf("Time of calculating maximum clique approximations for for all input graphs: %fs\n", maximal_clique_approximation_time);
    fprintf(outputFile, "Time of calculating maximum clique approximations for for all input graphs: %fs\n", maximal_clique_approximation_time);

    // printf("Time of calculating modular product for all input graphs: %fs\n", modular_product_time);
    // fprintf(outputFile, "Time of calculating modular product for all input graphs: %fs\n", modular_product_time);

    printf("Time of calculating maximum common subgraphs for all input graphs: %fs\n", maximal_clique_modular_product_time);
    fprintf(outputFile, "Time of calculating maximum common subgraphs for all input graphs: %fs\n", maximal_clique_modular_product_time);

    printf("Time of approximating maximum common subgraph for all input graphs: %fs\n", maximal_common_subgraph_approximation_time);
    fprintf(outputFile, "Time of approximating maximum common subgraph for all input graphs: %fs\n", maximal_common_subgraph_approximation_time);

    printf("Whole program execution time: %fs\n", (double)(time_all_end - time_all_begin) / CLOCKS_PER_SEC);
    fprintf(outputFile, "Whole program execution time: %fs\n", (double)(time_all_end - time_all_begin) / CLOCKS_PER_SEC);
    printf("\nResults have been saved to output.txt file\n");
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