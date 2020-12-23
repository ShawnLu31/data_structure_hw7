#include <stdio.h>
#include <stdlib.h>

#ifndef EDGE_H
#define EDGE_H
typedef struct Edge Edge;
struct Edge
{
    int index;//activities
    int starting_v;
    int ending_v;
    int weight;
};

typedef struct Element Element;
struct Element
{
    //element of list
    int index;//activities
    int weight;
    Element* link;
};

typedef struct List List;
struct List 
{
    //adjacency list
    int count;
    Element* link;
};


//primary function
void ReadFile(Edge e[], int num);
void CreateList(List list[], Edge e[], int num);
void CalEarly(List list[], int early[], int num);
void CalLate(List list[], int early[], int late[], int num);
void PrintResult(int early[], int late[], int num);
//tool function
void ZeroArray(int arr[], int len);
int Max(int a, int b);
int Min(int a, int b);
void PushStack(int stack[], int *top, int n);
int PopStack(int stack[], int *top);
#endif//EDGE_H