#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
struct adjacency_list
{
    int key;
    struct adjacency_list *next;
};

struct adjacency_list *new_node(struct adjacency_list *node, int key)
{
    struct adjacency_list *temp = malloc(sizeof(struct adjacency_list));
    temp->key = key;
    temp->next = node;
    return temp;
}

void make_adjacency_list(struct adjacency_list *adjacency_list[], int n, int **c, int m)
{
    for (int i = 0; i < n; i++)
    {
        adjacency_list[i] = NULL;
    }
    for (int i = 0; i < m; i++)
    {
         adjacency_list[c[i][0]] = new_node(adjacency_list[c[i][0]], c[i][1]);
        adjacency_list[c[i][1]] = new_node(adjacency_list[c[i][1]], c[i][0]);
        
    }
}


//number of nodes is n
//this implies that minimum number of edges to connect every node will be n-1
//counted the number of edges using dfs
// edges_count is incremented every time a new node is pushed into the stack
//stack is implicit in this case because I am using recursive DFS is used instead of iterative where actual stack is used

void DFS(int i, struct adjacency_list *adjacency_list[], int n, bool visited[])
{
    if (visited[i])
    {
        return;
    }
    visited[i] = true;
    struct adjacency_list *temp ;
    temp = adjacency_list[i];
    while (temp)
    {
        if (!visited[temp->key])
        {
            DFS(temp->key, adjacency_list, n, visited);
        }
        temp = temp->next;
    }
}

int makeConnected(int n, int **c, int m)
{
    struct adjacency_list *adjacency_list[n];
    make_adjacency_list(adjacency_list, n, c, m);
    

    //Initialising visited to false because initially no node is visited
    bool visited[n];
    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
    }
    //  printf("Edges count : %d\n")
    //each DFS will visit all the nodes connected to the source vertex hence number of dfs calls is the number of connected components
    int connected_comps = 0;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            connected_comps++;

            DFS(i, adjacency_list, n, visited);
        }
    }
    //no of edges is less than minimum no of edges required implies connecting every node is impossible
    // the number of elements in c is the number of edges in the graph 
    if (m < n - 1)
    {
        return -1;
    }
    
    //if connectionSize is > n-1 then it means there are enough edges
    //if there are 'n' connected components then we have to shift n-1 connected components to connect them all
    return connected_comps - 1;
}
void main ()    
{    
     
    int n;
    scanf("%d",&n);
    int m;
    scanf("%d",&m);
    int row=m, col=2;
    int ** c = (int**)malloc(sizeof(int*)*row);
    for(int i=0; i<row; i++)
        *(c+i) = (int*)malloc(sizeof(int)*col);
    for(int i=0; i<row; i++)
        {                     
            scanf("%d",&c[i][0]);
            scanf("%d",&c[i][1]);    
    }  
    printf("%d",makeConnected(n,c,row));
    for (int i=0; i<row; i++) {
        free(c[i]);
    }
    free(c);
}

