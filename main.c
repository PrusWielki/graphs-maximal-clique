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
    if (argc != 2)
    {
        printf("Usage \n");
        return 1;
    }

    FILE* filePtr = fopen(argv[1], "rb");

    if (filePtr == NULL)
    {
        printf("Error: could not open file %s", argv[1]);
        return 1;
    }

    size_t lineLength = 0;
    char *line = NULL;
    char* token;
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
                // Implement a better way to split the string
                for(int k=0; k<lineLength; k++)
                {
                    if(line[k]==13||line[k]==10)break;
                    if(line[k]==32)continue;


                    graphs[i].adjacencyMatrix[j*graphs[i].noOfVertices+k]=line[k]-'0';

#ifdef dbg
                    printf("file: %c\n",line[k]);
                    printf("new vertex in adj list: %d\n",graphs[i].adjacencyMatrix[j*graphs[i].noOfVertices+k]);
#endif // dbg

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
