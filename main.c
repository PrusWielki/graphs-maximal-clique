#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct Graph
{
    int noOfVertices;
    int* adjacencyMatrix;
    char* description;
} Graph;

void printGraph (struct Graph graph)
{

    printf("-------------------------------------------------\n");
    printf("Amount of vertices: %d\n",graph.noOfVertices);
    printf("Adjacency matrix:\n");
    for(int i=0; i<graph.noOfVertices*graph.noOfVertices; i++)
    {
        printf("%d",graph.adjacencyMatrix[i]);
        if(0==(i+1)%graph.noOfVertices)
            printf("\n");
        else
            printf(" ");
    }
    printf("Additional information: %s\n",graph.description);
    printf("-------------------------------------------------\n");
}

struct Graph* readGraphsFromFile(FILE* filePtr, int* noOfGraphs)
{



    size_t lineLength = 0;
    char* line = NULL;
    char* token = NULL;
    size_t bytesRead=0;
    int noOfVertices=0;


    // Read number of graphs in a file
    bytesRead=getline(&line, &lineLength, filePtr);

    if (0<bytesRead)
    {
        *noOfGraphs=strtol(line,NULL,10);

#ifdef dbg
        printf("file: %s\n", line);
        printf("Graphs: %d\n", *noOfGraphs);
#endif // dbg
    }



    struct Graph* graphs=malloc(*noOfGraphs*sizeof(Graph));



    for (int i = 0; i < *noOfGraphs; i++)
    {
        bytesRead=getline(&line, &lineLength, filePtr);

        if (0>=bytesRead)
            continue;

        noOfVertices=strtol(line,NULL,10);
        graphs[i].noOfVertices=noOfVertices;
#ifdef dbg
        printf("file: %s\n", line);
        printf("Vertices in graph %d: %d \n",i,graphs[i].noOfVertices);
#endif // dbg

        graphs[i].adjacencyMatrix=calloc(noOfVertices*noOfVertices,sizeof(int));
#ifdef dbg
        printf("New adj matrix[0]: %d\n",graphs[i].adjacencyMatrix[0]);
#endif // dbg
        for (int j = 0; j < noOfVertices; j++)
        {

            bytesRead=getline(&line, &lineLength, filePtr);
            if(0<bytesRead)
            {

                char *ptr = strtok(line, " ");
                int k=0;
                while(NULL != ptr)
                {
                    graphs[i].adjacencyMatrix[j*graphs[i].noOfVertices+k]=strtol(ptr,NULL,10);
#ifdef dbg
                    printf("file: %s\n",ptr);
                    printf("new vertex in adj list: %d\n",graphs[i].adjacencyMatrix[j*graphs[i].noOfVertices+k]);
#endif // dbg
                    ptr = strtok(NULL, " ");
                    k++;
                }
            }

        }

        bytesRead=getline(&line, &lineLength, filePtr);
        if(0<bytesRead)
        {
            graphs[i].description = malloc(strlen(line) + 1);
            strcpy(graphs[i].description, line);


#ifdef dbg
            printf("Additional graph information: %s\n",graphs[i].description);
#endif // dbg
        }

    }
    return graphs;
}


int main(int argc, char* argv[])
{
    // Initialization
    if (2 != argc)
    {
        printf("Usage \n");
        return 1;
    }
    FILE* filePtr = fopen(argv[1], "rb");

    if (NULL==filePtr)
    {
        printf("Error: could not open file %s", argv[1]);
        return 1;
    }

    // Read graphs from file
    struct Graph* graphs=NULL;
    int noOfGraphs=0;

    graphs=readGraphsFromFile(filePtr,&noOfGraphs);

    if(NULL==graphs)
        return -1;

    // Print graphs
    for(int i=0; i<noOfGraphs; i++)
    {
        printGraph(graphs[i]);
    }

    for(int i=0; i<noOfGraphs; i++)
    {
        free(graphs[i].adjacencyMatrix);
        free(graphs[i].description);
    }
    free(graphs);

    return 0;
}
