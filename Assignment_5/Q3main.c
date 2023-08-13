#include<stdio.h>
#include <stdlib.h>

int* city_population (int N, int* population, int** road, int Q, int** cities) ;

int main() {
    int N;
    scanf("%d", &N);
    int i_population;
    int *population = (int *)malloc(sizeof(int)*(N));
    for(i_population = 0; i_population < N; i_population++)
    	scanf("%d", &population[i_population]);
    int i_road, j_road;
    int **road = (int **)malloc((N-1)*sizeof(int *));
    for(i_road = 0; i_road < N-1; i_road++)
    {
    	road[i_road] = (int *)malloc((2)*sizeof(int));
    }
    for(i_road = 0; i_road < N-1; i_road++)
    {
    	for(j_road = 0; j_road < 2; j_road++)
    	{
    		scanf("%d", &road[i_road][j_road]);
    	}
    }
    int Q;
    scanf("%d", &Q);
    int i_cities, j_cities;
    int **cities = (int **)malloc((Q)*sizeof(int *));
    for(i_cities = 0; i_cities < Q; i_cities++)
    {
    	cities[i_cities] = (int *)malloc((3)*sizeof(int));
    }
    for(i_cities = 0; i_cities < Q; i_cities++)
    {
    	for(j_cities = 0; j_cities < 3; j_cities++)
    	{
    		scanf("%d", &cities[i_cities][j_cities]);
    	}
    }

    int* out_ = city_population(N, population, road, Q, cities);
    printf("%d", out_[0]);
    int i_out_;
    for(i_out_ = 1; i_out_ < Q; i_out_++)
    	printf("\n%d", out_[i_out_]);
}

///////
typedef struct _listnode
{
    int vertex;
    int pop;
	struct _listnode *next;
} ListNode;
typedef ListNode StackNode;

typedef struct _graph{
    int V;
    int E;
    ListNode **list;
}Graph;

typedef ListNode QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

/////
void printGraphList(Graph );

/////
int BFS (Graph g, int u, int v, int w);
int createGraph(int N, int* population, int** road, int Q, int** cities);
void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);

void printGraphList(Graph g){
    int i;
    ListNode* temp;

    for(i=0;i<g.V-1;i++)
    {
        //printf("%d:\t",i+1);
        temp = g.list[i];
        while(temp!=NULL){
            printf("V: %d, ",temp->vertex);
            printf("P: %d -> ",temp->pop);
            temp = temp->next;
        }
        printf("\n");
    }
}

void enqueue(Queue *qPtr, int item) {
    QueueNode *newNode;
    newNode = malloc( sizeof(QueueNode));
    if(newNode==NULL) exit(0);

    newNode->vertex = item;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr) {
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return 1;
    }
}

int getFront(Queue q){
    return q.head->vertex;
}

int isEmptyQueue(Queue q) {
    if(q.size==0) return 1;
    else return 0;
}

int* city_population (int N, int* population, int** road, int Q, int** cities)
{
    return createGraph(N, population, road, Q, cities);
}


int createGraph(int N, int* population, int** road, int Q, int** cities)
{
    Graph g;
    int i,j, count=0;
    int u=cities[0][0], v=cities[0][1], w=cities[0][2];
    ListNode *temp;

    g.V = N;
    g.list = (ListNode **) malloc(g.V*sizeof(ListNode *));

    for(i=0;i<g.V-1;i++)
        g.list[i] = NULL;

    // need to change this!!!!!!!!!!!!!!!!
    int lenRoad=4;

    //printf("len:%d\n", sizeof(road));
    //printf("len0:%d\n", sizeof(road[0]));
    //printf("lenRoad:%d\n", lenRoad);

    // joining 2 cities (vertices)
    for (i=0; i<lenRoad; i++)
    {
        for (j=0; j<2; j++)
        {
            if(g.list[i]==NULL)
            {
                g.list[i] = (ListNode *)malloc(sizeof(ListNode));
                g.list[i]->vertex = road[i][j];
                g.list[i]->pop = population[road[i][j]-1];
                g.list[i]->next = NULL;
            }
            else
            {
                temp = (ListNode *)malloc(sizeof(ListNode));
                g.list[i]->next = temp;
                temp->vertex = road[i][j];
                temp->pop = population[road[i][j]-1];
                temp->next = NULL;
            }
            g.E++;

        }
    }

    // BFS
    count = BFS(g, u, v, w);

    printGraphList(g);
    return count;
}

int BFS (Graph g, int u, int v, int w){
    Queue q;
    q.size = 0;
    q.head = NULL;
    q.tail = NULL;

    int i, curr;
    int visited[g.V], count=0;
    for (i = 0; i < g.V; i++) {
        visited[i] = 0;
    }

    enqueue(&q,v);
    visited[u-1] = 1;

    while(!isEmptyQueue(q)){
        curr = q.head->vertex;
        dequeue(&q);
        ListNode *temp = g.list[curr-1];
        while (temp != NULL) {
            int neighbor = temp->vertex;
            if (!visited[neighbor-1]) {
                enqueue(&q, neighbor);
                visited[neighbor-1] = 1;
                if (temp->pop <= w)
            }
            temp = temp->next;
            if (neighbor == w) return dist[neighbor-1];
        }

    }


    return -1;

}
