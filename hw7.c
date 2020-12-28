#include "gragh.h"
#define MAXSTACK 100

int main()
{
	//read number of activities (edges)
	int num_of_edge = 0;
	scanf("%d", &num_of_edge);
	if (num_of_edge <= 0 || num_of_edge >= 100)
	{
		printf("Too many edges.\n");
		exit(1);
	}
	Edge *edges = malloc(num_of_edge * sizeof(Edge)); //all edges
	//read edges
	ReadFile(edges, num_of_edge);
	//create adjacency list
	List *early_list = malloc(num_of_edge * sizeof(List));
	List *late_list = malloc(num_of_edge * sizeof(List));
	int num_of_vertex;
	num_of_vertex = CreateList(early_list, late_list, edges, num_of_edge);
	//calculate early time
	int early[num_of_edge];
	int early_v[num_of_vertex];
	ZeroArray(early, num_of_edge);
	ZeroArray(early_v, num_of_vertex);
	CalEarly(early_list, edges, early_v, early, num_of_vertex, num_of_edge);
	//calculate late time
	int late[num_of_edge];
	ZeroArray(late, num_of_edge);
	CalLate(late_list, edges, early_v, late, num_of_vertex, num_of_edge);

	PrintResult(early, late, num_of_edge);

	free(edges);
	free(early_list);
	free(late_list);
	return 0;
}

void ReadFile(Edge e[], int num_edge)
{
	for (int i = 0; i < num_edge; i++)
	{
		scanf("%d %d %d %d", &e[i].index, &e[i].starting_v, &e[i].ending_v, &e[i].weight);
	}
}

int CreateList(List early_list[], List late_list[], Edge e[], int num_edge)
{
	int i = 0;
	//find the first vertex and last vertex
	int first_v = 0;
	int last_v = 0;
	for (i = 0; i < num_edge; i++)
	{
		first_v = Min(first_v ,e[i].starting_v);//min
		last_v = Max(last_v, e[i].ending_v); //max
	}
	int num_v = last_v - first_v + 1;
	//init list
	for (i = 0; i < num_v; i++)
	{
		early_list[i].count = 0;
		late_list[i].count = 0;
		early_list[i].link = NULL;
		late_list[i].link = NULL;
	}
	//create early_list
	for (i = first_v; i < num_v + first_v; i++)
	{
		for (int k = 0; k < num_edge; k++)
		{ //find the vextex edge to which vertex
			if (i == e[k].starting_v)
			{
				Vertex *ver = malloc(sizeof(Vertex));
				ver->index = e[k].ending_v;
				ver->during = e[k].weight;
				ver->link = NULL;
				if (early_list[i].link == NULL)
				{
					early_list[i].link = ver;
					early_list[e[k].ending_v].count += 1;
				}
				else
				{
					Vertex *ptr = early_list[i].link;
					while (ptr->link != NULL)
					{
						ptr = ptr->link;
					}
					ptr->link = ver;
					early_list[e[k].ending_v].count += 1;
					ptr = NULL;
					free(ptr);
				}
			}
		}
	}
	//create late_list
	for (i = first_v; i < num_v + first_v; i++)
	{
		for (int k = 0; k < num_edge; k++)
		{ //find the vextex edge to which vertex
			if (i == e[k].ending_v)
			{
				Vertex *ver = malloc(sizeof(Vertex));
				ver->index = e[k].starting_v;
				ver->during = e[k].weight;
				ver->link = NULL;
				if (late_list[i].link == NULL)
				{
					late_list[i].link = ver;
					late_list[e[k].starting_v].count += 1;
				}
				else
				{
					Vertex *ptr = late_list[i].link;
					while (ptr->link != NULL)
					{
						ptr = ptr->link;
					}
					ptr->link = ver;
					late_list[e[k].starting_v].count += 1;
					ptr = NULL;
					free(ptr);
				}
			}
		}
	}

	return num_v;
}

void CalEarly(List list[], Edge e[], int early_v[], int early[], int num_v, int num_edge)
{
	int stack[MAXSTACK];
	int top = -1;
	//start
	int index = 0;
	Vertex *ptr = NULL;
	//cal early_v
	int first_v = 0;
	for (int i = 0; i < num_edge; i++)
	{
		first_v = Min(first_v ,e[i].starting_v);//min
	}
	PushStack(stack, &top, 0);
	while (top >= 0)
	{
		index = PopStack(stack, &top);
		if (list[index].count >= 0)
		{
			if (list[index].link != NULL)
			{
				ptr = list[index].link;
				do
				{
					//cal early
					early_v[ptr->index] = Max(early_v[ptr->index], ptr->during + early_v[index]);
					//push or --count
					if (list[ptr->index].count == 1)
					{
						PushStack(stack, &top, ptr->index);
					}
					else
					{
						--list[ptr->index].count;
					}
					//next link
					if (ptr->link == NULL)
					{
						break;
					}
					else
					{
						ptr = ptr->link;
					}
				} while (1 == 1);
			}
		}
	}
	//cal early edge
	for(int index = 0; index < num_edge; index++)
	{
		early[index] = early_v[e[index].starting_v];
		
	}
}

void CalLate(List list[], Edge e[], int early_v[], int late[], int num_v, int num_edge)
{
	//cal late vertex
	int late_v[num_v];
	int max = 0;
	for(int i = 0; i < num_v; i++)
	{
		max = Max(max, early_v[i]);
	}
	for(int i = 0; i < num_v; i++)
	{
		late_v[i] = max;
	}
	int stack[MAXSTACK];
	int top = -1;
	//start
	int index = 0;
	Vertex *ptr = NULL;
	int last_v = 0;
	for (int i = 0; i < num_edge; i++)
	{
		last_v = Max(last_v, e[i].ending_v); //max
	}
	PushStack(stack, &top, last_v);
	while (top >= 0)
	{
		index = PopStack(stack, &top);
		if (list[index].count <= 1)
		{
			if (list[index].link != NULL)
			{
				ptr = list[index].link;
				do
				{
					//cal early
					late_v[ptr->index] = Min(late_v[ptr->index], late_v[index] - ptr->during);
					//push or --count
					if (list[ptr->index].count == 1)
					{
						PushStack(stack, &top, ptr->index);
					}
					else
					{
						--list[ptr->index].count;
					}
					//next link
					if (ptr->link == NULL)
					{
						break;
					}
					else
					{
						ptr = ptr->link;
					}
				} while (1 == 1);
			}
		}
	}
	//cal late edge
	for(int index = 0; index < num_edge; index++)
	{
		late[index] = late_v[e[index].ending_v] - e[index].weight;
	}
}

void PrintResult(int early[], int late[], int num)
{
	for (int i = 0; i < num; i++)
	{
		printf("%d %d %d\n", i, early[i], late[i]);
	}
	//critical path
	for (int i = 0; i < num; i++)
	{
		if (early[i] == late[i])
		{
			printf("%d", i);
			if (i != num - 1)
				printf(" "); //not fianl edge
		}
	}
}

void ZeroArray(int arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		arr[i] = 0;
	}
}

int Max(int a, int b)
{
	return (a > b) ? a : b;
}
int Min(int a, int b)
{
	return (a < b) ? a : b;
}

void PushStack(int stack[], int *top, int n)
{
	if (*top >= MAXSTACK)
	{
		printf("Stack is full");
		return;
	}
	else
	{
		stack[++*top] = n;
	}
}
int PopStack(int stack[], int *top)
{
	if (*top < 0)
	{
		printf("Stack is empty");
		return 0;
	}
	else
	{
		int n = stack[*top];
		*top -= 1;
		return n;
	}
}