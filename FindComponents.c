// Faisal Shaikh
#include "Graph.h"
#include "List.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main (int argc, char*argv[])
{
    FILE *in, *out;
    int i = 0; // vertices

    if (argc != 3)
    {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // open files for reading and writing
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    if (in == NULL)
    {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if (out == NULL)
    {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // begin graph
    fscanf(in, "%d", &i);
    Graph G = newGraph(i);
    int u = 0;
    int v = 0;

    // fill graph
    int flag = 1;
    while (flag !=0)
    {
        fscanf(in, "%d %d", &u, &v);
        if(u == 0 && v == 0)
        {
            flag = 0;
            break;
        }
        addArc(G,u,v);
    }

    // perform DFS
    List list = newList(); // new List
    for (int j = 1; j <= getOrder(G); j++)
    {
        append(list, j);
    }
    DFS(G, list);
    Graph transposedGraph = transpose(G);
    DFS(transposedGraph, list);

    int scc = 0;
    moveFront(list);
    for (int j = 1  ; j <= getOrder(transposedGraph); j++)
    {
        int c = get(list);
        if (getParent(transposedGraph, c) == NIL)
        {
            scc++;
        }
        moveNext(list);
    }

    fprintf(out, "Adjacency list representation of G: \n");
    printGraph(out, G);

    fprintf(out, "\nG contains %d strongly connected components: ", scc);

    // strongly connect components
    List outList = newList();
    moveFront(list);
    prepend(outList, get(list));
    moveBack(outList);

    moveNext(list);

    int g = 0;

    while(index(list) != -1)
    {
        g = get(list);

        if(getParent(transposedGraph, g) != NIL)
        {
            insertAfter(outList, g);
            moveNext(outList);
        }
        else
        {
            prepend(outList, g);
            moveFront(outList);
        }
        moveNext(list);
    }

    int cc = 1;
    moveFront(outList);
    while(index(outList) != -1)
    {
        g = get(outList);
        if(getParent(transposedGraph, g) == NIL)
        {
            fprintf(out, "\nComponent %d: %d ", cc, g);
            moveNext(outList);
            cc++;
        }
        else
        {
            fprintf(out, "%d ", g);
            moveNext(outList);
        }
    }

    // end line at the end of file
    fprintf(out, "\n");

    // free everything at the end and close files
    freeList(&list);
    freeList(&outList);
    freeGraph(&G);
    freeGraph(&transposedGraph);
    fclose(in);
    fclose(out);
    return (0);
}
