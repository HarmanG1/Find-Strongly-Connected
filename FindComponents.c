/********************************************************************************* 
* Harman Gidha, hgidha 
* Main File
* FindComponents.c 
*********************************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char * argv[])
{
    FILE *in, *out;

    // check command line for correct number of arguments
    if( argc != 3 ){
        fprintf(stderr, "Error: two arguments needed. Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // open files for reading and writing 
    in = fopen(argv[1], "r");
        if( in==NULL ){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    out = fopen(argv[2], "w");
    if( out==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    int n = 0;
    fscanf(in, "%d", &n);
    Graph g = newGraph(n);

    int x = -1;
    int y = -1;
    fscanf(in, "%d", &x);
    fscanf(in, "%d", &y);
    while(x != 0 && y != 0)
    {
        addArc(g, x, y);
        fscanf(in, "%d", &x);
        fscanf(in, "%d", &y);
    }

    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, g);
    fprintf(out, "\n");    

    List l = newList();
    for(int i = 1; i <= n; i++)
    {
        append(l, i);
    }

    Graph gt = transpose(g);
    DFS(g, l);
    DFS(gt, l);

    int strcc = 0;
    for(int x = 1; x <= getOrder(gt); x++)
    {
        if(getParent(gt, x) == NIL)
        {
            strcc+= 1;
        }
    }

    fprintf(out, "G contains %d strongly connected components:\n", strcc);

    List *rl = calloc(strcc, sizeof(List));
    for(int i = 0; i < strcc; i++)
    {
        rl[i] = newList();
    }

    int lin = strcc;
    moveFront(l);
    while(index(l) >= 0)
    {
        if(getParent(gt, get(l)) == NIL)
        {
            lin--;
            append(rl[lin], get(l));
        }
        else
        {
            append(rl[lin], get(l));
        }
        moveNext(l);
    }

    int comp = 1;
    for(int i = 0; i < strcc; i++)
    {
        fprintf(out, "Component %d: ", comp);
        printList(out, rl[i]);
        fprintf(out,"\n");
        comp++;
    }        

    for(int i = 0; i < strcc; i++)
    {
        freeList(&rl[i]);
    }
    free(rl);
    freeGraph(&g);
    freeGraph(&gt);
    freeList(&l);
    fclose(in);
    fclose(out);

    return 0;
}
