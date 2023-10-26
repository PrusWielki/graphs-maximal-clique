#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"graph.h"

int getIntLine(FILE* file) {
    char* line;
    fgets(line, 1000, file);
    return atoi(line);
}

struct Graph* getInputGraphs(char* fileName) {
    FILE* filePtr = fopen(argv[1], "rb");

    if (filePtr == NULL) {
        printf("Error: could not open file %s", argv[1]);
        return 1;
    }

    int noOfGraphs = getIntLine(filePtr);
    struct Graph graphs[noOfGraphs];
    for (int i = 0; i < noOfGraphs; i++) {
        int noOfVertices = getIntLine(filePtr);
        char **matrixRows = (char **)malloc(noOfVertices * sizeof(char *));

        for (int j = 0; j < noOfVertices; j++) {
            char *line = NULL;
            size_t lineLength = 0;
            ssize_t bytesRead = getline(&line, &lineLength, filePtr);
            
            if (bytesRead != -1) {
                if (bytesRead > 0 && line[bytesRead - 1] == '\n') {
                    line[bytesRead - 1] = '\0';
                }
                matrixRows[j] = line;
                printf("Line: %s\n", matrixRows[j]);
            }
        }
        graphs[0] = initGraph(noOfVertices, matrixRows);
    }
    return graphs;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage \n");
        return 1;
    }
    struct Graphs* input = getInputGraphs(argv[1]);
    return 0;
}
