#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u;
    int v;
} Edge;

int readgraph (Edge **edges, int *numEdges, int *numVertices) {
    FILE *pFile = fopen("incidencematrix.txt", "r");
    if (pFile == NULL) {
        printf("Error opening file");
        return 1;
    }
    fscanf(pFile, "%d %d", numVertices, numEdges);
    *edges = malloc((*numEdges) * sizeof(Edge));
    if (*edges==NULL) {
        printf("Memory allocation failed");
        return 1;
    }
    int IncidenceMatrix[*numEdges][*numVertices];
    for (int i = 0; i < *numEdges; i++) {
        for (int j = 0; j < *numVertices; j++) {
            fscanf(pFile, "%d", &IncidenceMatrix[i][j]);
        }
    }
    for (int i = 0; i < *numEdges; i++) {
        for (int j = 0; j < *numVertices; j++) {
            printf("%d ", IncidenceMatrix[i][j]);
        }
        printf("\n");
    }
    printf("========================================\n");
    for (int i = 0; i < *numEdges; i++) {
    (*edges)[i].u = -1;
    (*edges)[i].v = -1;
    int count = 0;
    for (int j = 0; j < *numVertices; j++) {
        if (IncidenceMatrix[i][j] == 1) {
            count++;
            if (count == 1) {
                (*edges)[i].u = j + 1;
            } else if (count == 2) {
                (*edges)[i].v = j + 1;
            } else {
                printf("WARNING: Edge %d is connected to more than two vertices\n", i+1);
            }
        }
    }
    }
    fclose(pFile);
    return 0;
}

int printEdges (Edge *edges, int *numEdges) {
    printf("Graph Edges: \n");
    for (int i = 0; i < *numEdges; i++ ) {
        printf("(%d, %d)\n", edges[i].u, edges[i].v );
    }
    return 0;
}

int writeDotFile(Edge *edges, int numEdges, const char *outputFile, int Ver) {
    FILE *dotFile = fopen(outputFile, "w");
    if (dotFile==NULL) {
        printf("Error opening file");
        return 1;
    }
    fprintf(dotFile, "graph G {\n");
    for (int i = 0; i < Ver; i++) {
        fprintf(dotFile, "    %d;\n", i+1);
    }
    for (int i = 0; i < numEdges; i++) {
        fprintf(dotFile, "    %d -- %d;\n", edges[i].u, edges[i].v);
    }
    fprintf(dotFile, "}\n");
    fclose(dotFile);
    system("dot -Tpng Graph.dot -o graph.png");
    return 0;
}

int main() {
    Edge *edges;
    int numEdges, numVertices;
    readgraph(&edges, &numEdges, &numVertices);
    printEdges(edges, &numEdges);
    writeDotFile(edges, numEdges, "Graph.dot", numVertices);
    free(edges);
    edges = NULL;
    return 0;
}
