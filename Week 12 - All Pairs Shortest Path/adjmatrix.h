/* adjmatrix.h */
/* NOTE: this could be made a lot more robust, 
    but it's easier not to. */
#include <limits.h>
#define NOPATH INT_MAX/2
/* Allocates space for a size * size array
    and sets array[i][i] = 0, others are the NOPATH value. */
int **newMatrix(int size);

/* Adds an edge between one given index and another. */
void addEdge(int **adjMatrix, int src, int dst, int weight);

/* Frees a matrix allocated with the newMatrix function. */
void freeMatrix(int **matrix, int size);
