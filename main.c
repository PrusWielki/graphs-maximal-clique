#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define dbg

struct Graph
{
    int noOfVertices;
    int* adjacencyMatrix;
    char* description;
} Graph;



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

    size_t lineLength = 0;
    char* line = NULL;
    char* token = NULL;
    size_t bytesRead=0;
    int noOfVertices=0;
    int noOfGraphs=0;


    // Read number of graphs in a file
    bytesRead=getline(&line, &lineLength, filePtr);

    if (0<bytesRead)
    {
        noOfGraphs=atoi(line);

#ifdef dbg
        printf("file: %s\n", line);
        printf("Graphs: %d\n", noOfGraphs);
#endif // dbg
    }



    struct Graph* graphs=malloc(noOfGraphs*sizeof(Graph));



    for (int i = 0; i < noOfGraphs; i++)
    {
        bytesRead=getline(&line, &lineLength, filePtr);

        if (0>=bytesRead)
            continue;

        noOfVertices=atoi(line);
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
                    graphs[i].adjacencyMatrix[j*graphs[i].noOfVertices+k]=atoi(ptr);
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
            graphs[i].description=line;

#ifdef dbg
            printf("Additional graph information: %s\n",graphs[i].description);
#endif // dbg
        }

    }

    return 0;
}
