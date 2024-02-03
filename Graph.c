/********************************************************************************* 
* Harman Gidha, hgidha 
* Graph.c 
*********************************************************************************/ 

#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

struct GraphObj{
   List *Neigh; //An array of Lists whose ith element contains the neighbors of vertex i.
   int *color; //An array of ints (or chars, or strings) whose ith element is the color (white, gray, black) of vertex i
   int *parent; //An array of ints whose ith element is the parent of vertex i.
   int *dis; 
   int order; //number of vertices 
   int size; //number of edges
   int *fin;
} GraphObj;

Graph newGraph(int n)
{
   Graph g;
   g = malloc(sizeof(GraphObj));
   assert(g!=NULL);
   g->order = n;
   g->size = 0;

   g->Neigh = calloc(n+1, sizeof(List));
   g->color = calloc(n+1, sizeof(int));
   g->parent = calloc(n+1, sizeof(int));
   g->dis = calloc(n+1, sizeof(int));
   g->fin = calloc(n+1, sizeof(int));

   for(int i = 1; i <= n; i++)
   {
      g->Neigh[i] = newList();
      g->color[i] = White;
      g->parent[i] = NIL;
      g->dis[i] = UNDEF;
      g->fin[i] = UNDEF;
   }
   return g;
}

void freeGraph(Graph* pG)
{
   if(pG != NULL && *pG != NULL)
   {
      for(int i = 0; i <= (*pG)->order; i++)
      {
         freeList(&(*pG)->Neigh[i]);
      }
      free((*pG)->Neigh);
      free((*pG)->color);
      free((*pG)->parent);
      free((*pG)->dis);
      free((*pG)->fin);
      free((*pG));
      *pG = NULL;
   }
}

int getOrder(Graph G)
{
   if(G == NULL)
   {
      fprintf(stderr, "Error: graph is Null\n");
      exit(EXIT_FAILURE);
   }
   return G->order;
}

int getSize(Graph G)
{
   if(G == NULL)
   {
      fprintf(stderr, "Error: graph is Null\n");
      exit(EXIT_FAILURE);
   }
   return G->size;
}

int getParent(Graph G, int u)
{
   if(G == NULL)
   {
      fprintf(stderr, "Error: graph is Null\n");
      exit(EXIT_FAILURE);
   }
   if(u < 1 ||u > getOrder(G))
   {
      fprintf(stderr, "Error: Precondition for u not met\n");
      exit(EXIT_FAILURE);
   }
   return G->parent[u];
}

int getDiscover(Graph G, int u) /* Pre: 1<=u<=n=getOrder(G) */
{
   if(G == NULL)
   {
      fprintf(stderr, "Error: graph is Null\n");
      exit(EXIT_FAILURE);
   }
   if(u < 1 ||u > getOrder(G))
   {
      fprintf(stderr, "Error: Precondition for u not met\n");
      exit(EXIT_FAILURE);
   }
   return G->dis[u];
}

int getFinish(Graph G, int u) /* Pre: 1<=u<=n=getOrder(G) */
{
   if(G == NULL)
   {
      fprintf(stderr, "Error: graph is Null\n");
      exit(EXIT_FAILURE);
   }
   if(u < 1 ||u > getOrder(G))
   {
      fprintf(stderr, "Error: Precondition for u not met\n");
      exit(EXIT_FAILURE);
   }
   return G->fin[u];
}

void addEdge(Graph G, int u, int v)
{
   if(G == NULL)
   {
      fprintf(stderr, "Error: graph is Null\n");
      exit(EXIT_FAILURE);
   }
   if(u < 1 ||u > getOrder(G))
   {
      fprintf(stderr, "Error: Precondition for u not met\n");
      exit(EXIT_FAILURE);
   }
   if(v < 1 ||v > getOrder(G))
   {
      fprintf(stderr, "Error: Precondition for v not met\n");
      exit(EXIT_FAILURE);
   }
   addArc(G, u, v);
   addArc(G, v, u);
   G->size = G->size - 1;
}

void addArc(Graph G, int u, int v)
{
   if(G == NULL)
   {
      fprintf(stderr, "Error: graph is Null\n");
      exit(EXIT_FAILURE);
   }
   if(u < 1 ||u > getOrder(G))
   {
      fprintf(stderr, "Error: Precondition for u not met\n");
      exit(EXIT_FAILURE);
   }
   if(v < 1 ||v > getOrder(G))
   {
      fprintf(stderr, "Error: Precondition for v not met\n");
      exit(EXIT_FAILURE);
   }

   bool inserted = false;
   moveFront(G->Neigh[u]);
   while(index(G->Neigh[u]) >= 0)
   {
      if(get(G->Neigh[u]) == v)
      {
         return;
      }
      moveNext(G->Neigh[u]);
   }
   
   moveFront(G->Neigh[u]);
   while(!inserted)
   {
      if(index(G->Neigh[u]) == -1)
      {
         append(G->Neigh[u], v);
         inserted = true;
      }
      else if(v < get(G->Neigh[u]))
      {
         insertBefore(G->Neigh[u], v);
         inserted = true;
      }
      else
      {
         moveNext(G->Neigh[u]);
      }
   }
   G->size+= 1;
}

void Vist(Graph G, List S, int x, int *time)
{
   G->dis[x] = ++(*time);
   G->color[x] = Gray;
   moveFront(G->Neigh[x]);
   while(index(G->Neigh[x]) != -1)
   {
      int y = get(G->Neigh[x]);
      if(G->color[y] == White)
      {
         G->parent[y] = x;
         Vist(G, S, y, time);
      }
      moveNext(G->Neigh[x]);
   }
   G->color[x] = Black;
   G->fin[x] = ++(*time);
   prepend(S, x);
}

void DFS(Graph G, List S) /* Pre: length(S)==getOrder(G) */
{
   if(G == NULL)
   {
      fprintf(stderr, "Error: graph is Null\n");
      exit(EXIT_FAILURE);
   }
   if(length(S) != getOrder(G))
   {
      fprintf(stderr, "Error: Precondition for length of S is not met\n");
      exit(EXIT_FAILURE);
   }

   for(int x = 0; x <= G->order; x++)
   {
      G->color[x] = White;
      G->parent[x] = NIL;
   }
   int time = 0;
   moveFront(S);
   while(index(S) >= 0)
   {
      if(G->color[get(S)] == White)
      {
         Vist(G, S, get(S), &time);
      }
      moveNext(S);
   }
   for(int x = 1; x <= G->order; x++)
   {
      deleteBack(S);
   }
}

Graph transpose(Graph G)
{
   if(G == NULL)
   {
      fprintf(stderr, "Error: graph is Null\n");
      exit(EXIT_FAILURE);
   }

   Graph C = newGraph(G->order);
   for(int x = 1; x <= G->order; x++)
   {
      moveFront(G->Neigh[x]);
      while(index(G->Neigh[x]) >= 0)
      {
         addArc(C, get(G->Neigh[x]), x);
         moveNext(G->Neigh[x]);
      }
   }
   return C;
}

Graph copyGraph(Graph G)
{
   if(G == NULL)
   {
      fprintf(stderr, "Error: graph is Null\n");
      exit(EXIT_FAILURE);
   }

   Graph C = newGraph(G->order);
   for(int x = 1; x <= G->order; x++)
   {
      moveFront(G->Neigh[x]);
      while(index(G->Neigh[x]) >= 0)
      {
         addArc(C, x, get(G->Neigh[x]));
         moveNext(G->Neigh[x]);
      }
   }
   return C;
}

void printGraph(FILE* out, Graph G)
{
   if(G == NULL)
   {
      fprintf(stderr, "Error: graph is Null\n");
      exit(EXIT_FAILURE);
   }
   for(int i = 1; i <= G->order; i++)
   {
      fprintf(out, "%d: ", i);
      printList(out, G->Neigh[i]);
      fprintf(out, "\n");
   }
}
