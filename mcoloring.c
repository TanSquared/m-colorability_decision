#include<stdio.h>
#include<stdlib.h>

void printcolor(int *nc, int size)
{
    printf("The respective colors starting from node 1 to node %d are\n[", size);
    int i;
    for(i = 0; i < size-1; i++)
    {
        printf("%d, ", *(nc + i));
    }
    printf("%d]\n", *(nc + size - 1));
}

void nodecolor(int **g, int *nc, int i, int size)
{
    *(nc + i) = ((*(nc + i)) + 1) % (size + 1);
    if(*(nc + i) == 0) return;
    for(int j = 0; j < size; j++)
    {
        if(*((*(g + i)) + j) == 1 && *(nc + i) == *(nc + j))
        {
            nodecolor(g, nc, i, size);
            return;
        }
    }
}

void graphcolor(int **g, int *nc, int size)
{
    for(int i = 0; i < size; i++)
    {
        nodecolor(g, nc, i, size);
        if(*(nc + i) == 0)
        {
            printf("There's no feasible solution\n");
            return;
        }
    }
    printcolor(nc, size);
}

int main()
{
    int size, i, j;
    printf("Enter the number of nodes that you want: ");
    scanf("%d", &size);
    int **g = (int **)malloc(size * sizeof(int *));
    for(i = 0; i < size; i++)
        *(g + i) = (int *)calloc(size, sizeof(int));
    int *nc = (int *)calloc(size, sizeof(int));
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            if(i == j)
            continue;
            if(i > j)
            {
                *((*(g + i)) + j) = *((*(g + j)) + i);
                continue;
            }
            printf("Enter value of edge (%d, %d): ", i+ 1, j + 1);
            scanf("%d", (*(g + i)) + j);
        }
    }
    graphcolor(g, nc, size);
    for(i = 0; i < size; i++)
    free(*(g + i));
    free(nc);
    return 0;
}