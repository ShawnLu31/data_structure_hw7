#### F740860872 呂文翔
# data_structure_hw7
## Result screenshot
* compile:
![image](https://github.com/ShawnLu31/data_structure_hw7/blob/main/compile.JPG)
* execution:
![image](https://github.com/ShawnLu31/data_structure_hw7/blob/main/execution.JPG)
* comparison:
![image](https://github.com/ShawnLu31/data_structure_hw7/blob/main/diff.JPG)
## Program sturcture
* 流程圖:  
![image](https://github.com/ShawnLu31/data_structure_hw7/blob/main/structure.png)
## Program functions
### Main
  * Parameter 
    + int num_of_edge: the number of edges.
    + int num_of_vertex: the number of vertexs.
    + List *early_list: adjacency list for calculating the earliest time.
    + List *late_list: inverted adjacency list for calculating the latest time.
    + int early_v[]: the earliest time of vertexs.
    + int early[]: the earliest time of edges.
    + int late[]: the latest time of edges.
### Read the file (read the activities)
* `void ReadFile(Edge e[], int num)`  
  Read the information of activities(i.e. edges) in the input file.  
  * information:  
    - activity i
    - starting vertex j
    - ending vertex k
    - weight w
  * Parameter 
    + Edge e[]: store the information of edges.
    + int num: the number of edges.
### Create adjacency list
* `int CreateList(List early_list[], List late_list[], Edge e[], int num_edge)`  
  Create adjacency list (early_list) and inverted adjacency list (late_list).
  * Parameter 
    + List early_list[]: adjacency list.
    + List late_list[]: inverted adjacency list.
    + Edge e[]: the information of edges.
    + int num_edge: the number of edges.
  * Return Value
### Calulate the earliest time
* `void CalEarly(List list[], Edge e[], int early_v[], int early[], int num_v, int num_edge)`  
    Calculate the earliest time of vertexs.  
    Use it to calculate earliest time of edges.  
  * Parameter 
    + List list[]: adjacency list.
    + Edge e[]: the information of edges.
    + int early_v[]: the earliest time of vertexs.
    + int early[]: the earliest time of edges.
    + int num_v: the number of vertexs.
    + int num_edge: the number of edges.
### Calulate the latesst time
* `void CalLate(List list[], Edge e[], int early_v[], int late[], int num_v, int num_edge)`  
    Calculate the latest time of vertexs.  
    Use it and early_v to calculate latest time of edges.  
  * Parameter 
    + List list[]: inverted adjacency list.
    + Edge e[]: the information of edges.
    + int early_v[]: the earliest time of vertexs.
    + int late[]: the latest time of edges.
    + int num_v: the number of vertexs.
    + int num_edge: the number of edges.
### Print the result
* `void PrintResult(int early[], int late[], int num)`  
  Print the early-late time of each activity in ascending order.  
  Print Criticla paths in ascending order.  
  * Parameter 
    + int early[]
    + int late[]
    + int num: the number of edges.
## Program Design
* ## struct
### Edge
```c
struct Edge
{
    int index;
    int starting_v;
    int ending_v;
    int weight;
};
```
### Vertex
```c
struct Vertex
{
    //Vertex of list
    int index;//此vertex(in list)指向的vertex的index
    int during;//兩vertex之間的edge的weight
    Vertex* link;
};
```
### List
```c
struct List 
{
    //adjacency list
    int count;//the number of edge指向此vertex
    Vertex* link;
};
```
* ## Create adjacency list
1. find the starting vertex and ending vertex of the gragh.
### adjacency list
i from starting vertex to ending vertex    
if starting-_v of edges[i]  == i  
{  
put the ending_v and weight of edges[i] in list  
list[ending_v].count + 1;  
}

### inverted adjacency list
i from ending vertex to starting vertex    
if endting-_v of edges[i]  == i  
{  
put the starting_v and weight of edges[i] in list  
list[starting_v].count + 1;  
}
* ## Calculate early-late time
### Calculate the earliest time of vertexs
Use adjacency list(early_list) to calulate earliset time of vertexs.
### Calculate the earliest time of edges
Use earliset time of vertex to calculate earliset time of edges.
* 
### Calculate the latest time of vertexs 
Use inverted adjacency list(late_list) to calcute latest time of vertexs.
### Calculate the latest time of edges
Use latest time of vertexs to calculate latest time of edges.
* 
* ### Find critical paths
if the early time of the edge i is equal to the late time of the edge i,  
the edge i is on critical path.
