#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <float.h>

typedef struct vertices{
    int* data;
    int id;
}Vertex;

typedef struct graph{
    int users;
    Vertex* V;
    double* Edges;
}Graph;

char * * explode(const char * str, const char * delims, int * arrLen);

Vertex create_Vertex(int id, int data1, int data2, int data3, int data4, int data5, int data6, int data7, int data8);    

Graph create_empty_Graph(int users, Vertex* Vertex_Array);

void print_graph(Graph graph);

double calc_UL(Vertex user1, Vertex user2);

double find_max(Graph G);

Graph UNnorm_Graph(Graph G);

Graph norm_Graph(double max, float lambda, Graph G);

int* Query3(Graph G, int queryNode);

double Query5(Graph G);

int minDist(Graph G, float* dist, int* S);

void print_Dijkstras(float* dist, Graph G);

int Query2(Graph G, int queryNode, float alpha);

void queue(int** Queue, int node, int* front, int* rear, Graph G);

int delete(int** Queue, int* front, int* rear);

int isEmpty(int* front, int* rear);

int cmpfunc(const void * a, const void * b);

int Query4(Graph G, int queryNode, int display);

void Query6(Graph G);
