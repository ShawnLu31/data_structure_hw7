#include <stdio.h>
#include <stdlib.h>

#ifndef GRAGH_H
#define GRAGH_H
typedef struct Edge Edge;
struct Edge
{
    int index;//activities
    int starting_v;
    int ending_v;
    int weight;
};

typedef struct Vertex Vertex;
struct Vertex
{
    //Vertex of list
    int index;//activities
    int during;
    Vertex* link;
};

typedef struct List List;
struct List 
{
    //adjacency list
    int count;
    Vertex* link;
};


//primary function
void ReadFile(Edge e[], int num);
int CreateList(List early_list[], List late_list[], Edge e[], int num);
void CalEarly(List list[], Edge e[], int early_v[], int early[], int num_v, int num_edge);
void CalLate(List list[], Edge e[], int early_v[], int late[], int num_v, int num_edge);
void PrintResult(int early[], int late[], int num);
//tool function
void ZeroArray(int arr[], int len);
int Max(int a, int b);
int Min(int a, int b);
void PushStack(int stack[], int *top, int n);
int PopStack(int stack[], int *top);
#endif//GRAGH_H