/********************************************************************************* 
* Harman Gidha, hgidha 
* GraphTest.c 
*********************************************************************************/ 

#include "List.h"
#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

int main(int argc, char* argv[])
{
    int n = 8;
    Graph A = newGraph(n);
    Graph B = newGraph(n);
    List S = newList();
    List L = newList();
    
    for(int i=1; i<=n; i++) append(S, i);
    for(int i=1; i<=n; i++) append(L, i);

    addArc(A, 1,2);
    addArc(A, 1,5);
    addArc(A, 2,5);
    addArc(A, 2,6);
    addArc(A, 3,2);
    addArc(A, 3,4);
    addArc(A, 3,6);
    addArc(A, 3,7);
    addArc(A, 3,8);
    addArc(A, 6,5);
    addArc(A, 6,7);
    addArc(A, 8,4);
    addArc(A, 8,7);

    addArc(B, 1,2);
    addArc(B, 1,5);
    addArc(B, 2,5);
    addArc(B, 2,6);
    addArc(B, 3,2);
    addArc(B, 3,4);
    addArc(B, 3,6);
    addArc(B, 3,7);
    addArc(B, 3,8);
    addArc(B, 6,5);
    addArc(B, 6,7);
    addArc(B, 8,4);
    addArc(B, 8,7);

    printf("Graph A print 1:\n");
    printGraph(stdout, A);
    printf("Graph B print 1:\n");
    printGraph(stdout, B); //Should both be the same
    printf("\n");

    assert(getOrder(A) == getOrder(B));
    assert(getSize(A) == getSize(B));
    assert(getParent(A, 1) == getParent(B, 1));
    assert(getDiscover(A, 1) == getDiscover(B, 1));
    assert(getFinish(A, 1) == getFinish(B, 1));
    
    DFS(A, S);
    DFS(B, L);

    assert(getParent(A, 1) == getParent(B, 1));
    assert(getDiscover(A, 1) == getDiscover(B, 1));
    assert(getFinish(A, 1) == getFinish(B, 1));
    assert(equals(S, L));

    Graph T = transpose(A);
    T = transpose(T);
    
    printf("Graph A print 2:\n");
    printGraph(stdout, A);
    printf("Graph T print 2:\n");
    printGraph(stdout, T); //Should both be the same
    printf("\n");

    Graph C = copyGraph(B);

    printf("Graph C print 3:\n");
    printGraph(stdout, C);
    printf("Graph B print 3:\n");
    printGraph(stdout, B); //Should both be the same
    printf("\n");

    freeGraph(&A);
    freeGraph(&B);
    freeList(&S);
    freeList(&L);

    return 0;
}
