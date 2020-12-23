#include "edge.h"
#define MAXSTACK 100

int main(){
	//read number of activities (edges)
	int num_of_edge = 0;
	scanf("%d", &num_of_edge);
	if(num_of_edge <= 0 || num_of_edge >= 100)
	{
		printf("Too many edges.\n");
		exit(1);
	}
	Edge *edges = malloc(num_of_edge * sizeof(Edge));//all edges
	//read edges
	ReadFile(edges, num_of_edge);
	//create adjacency list
	List *list = malloc(num_of_edge * sizeof(List));
	CreateList(list, edges, num_of_edge);
	//calculate early time
	int early[num_of_edge];
	ZeroArray(early, num_of_edge);
	CalEarly(list, early, num_of_edge);
	//calculate late time
	int late[num_of_edge];
	ZeroArray(late, num_of_edge);
	CalLate(list, early, late, num_of_edge);

	PrintResult(early, late, num_of_edge);

	free(edges);
	free(list);
	return 0;
}

void ReadFile(Edge e[], int num)
{
	for(int i = 0; i < num; i++){
		scanf("%d %d %d %d", &e[i].index, &e[i].starting_v, &e[i].ending_v, &e[i].weight);
	}
}

void CreateList(List list[], Edge e[], int num)
{
	int i = 0;
	//init list
	for(i = 0; i < num; i++)
	{
		list[i].count = 0;
		list[i].link = NULL;
	}
	
	//find the first vertex and last vertex
	int first_v = 0;
	int last_v = 0;
	for(i = 0; i < num; i++)
	{
		if(e[i].starting_v < first_v){
			first_v = e[i].starting_v;//min
		}
		if(e[i].ending_v > last_v){
			last_v = e[i].ending_v;//max
		}
	}
	//create list
	for(i = 0; i < num; i++)
	{
		for(int k = 0; k < num; k++)
		{//find the edge "e[i]" connect to
			if(e[i].ending_v == last_v)
			{
				break;
			}
			else if(e[i].ending_v == e[k].starting_v)
			{
				Element *ele = malloc(sizeof(Element));
				ele->index = e[k].index;
				ele->weight = e[i].weight;
				ele->link = NULL;
				if(list[e[i].index].link == NULL)
				{
					list[e[i].index].link = ele;
					++list[e[k].index].count;
				}
				else
				{
					Element* ptr = list[e[i].index].link;
					while (ptr->link != NULL)
					{
						ptr = ptr->link;
					}
					ptr->link = ele;
					++list[e[k].index].count;		
					ptr = NULL;
					free(ptr);
				}
			}
		}
	}
}

void CalEarly(List list[], int early[], int num)
{
	int stack[MAXSTACK];
	int top = -1;
	//start
	int index = 0;
	Element *ptr = NULL;
	for(int i = 0; i < num; i++)
	{// starting points
		if(list[i].count == 0)
		{
			PushStack(stack, &top, i);
			while (top >= 0)
			{
				index = PopStack(stack, &top);
				if(list[index].count <= 1)
				{
					if(list[index].link != NULL)
					{
						ptr = list[index].link;
						do{
							//cal early
							early[ptr->index] = Max(early[ptr->index], ptr->weight + early[index]);
							//push or --count
							if(list[ptr->index].count <= 1)
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
						}while (1 == 1);
					}
				}
			}
		}
	}
}

void CalLate(List list[], int early[], int late[], int num)
{
	//init late
	int max_w = 0;
	for(int i = num - 1; i >= 0; i--)
	{
		if(early[i] > max_w)
			max_w = early[i];
	}
	for(int i = num - 1; i >= 0; i--)
	{
		if(list[i].link == NULL)
			late[i] = early[i];
		else
		{
			late[i] = max_w;
		}
	}
	Element *ptr = NULL;
	for(int index = num - 1; index >= 0; index--)
	{
		if (list[index].link != NULL)
		{
			ptr = list[index].link;
			do{
				//cal late
				late[index] = Min(late[index], late[ptr->index] - ptr->weight);
				//next link
				if (ptr->link == NULL)
				{
					break;
				}
				else
				{
					ptr = ptr->link;
				}
			}while (1 == 1);
		}
	}
}

void PrintResult(int early[], int late[], int num)
{
	for(int i = 0; i < num; i++)
	{
		printf("%d %d %d\n", i, early[i], late[i]);
	}
	//critical path
	for(int i = 0; i < num; i++)
	{
		if(early[i] == late[i])
		{
			printf("%d", i);
			if(i != num -1)
				printf(" ");//not fianl edge
		}
	}
}

void ZeroArray(int arr[], int len)
{
	for(int i = 0; i < len; i++){
		arr[i] = 0;
	}
}

int Max(int a, int b)
{
	return (a > b)? a:b;
}
int Min(int a, int b)
{
	return (a < b)? a:b;
}

void PushStack(int stack[], int *top, int n)
{
	if(*top >= MAXSTACK)
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
	if(*top < 0)
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