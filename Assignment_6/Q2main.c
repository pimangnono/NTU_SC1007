#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
    struct _listnode *next;
} ListNode;
typedef ListNode StackNode;

typedef struct _graph
{
    int V;
    int E;
    ListNode **list;
} Graph;

typedef ListNode QueueNode;

typedef struct _stack
{
    int size;
    StackNode *head;
} Stack;

void insertAdjVertex(ListNode **AdjList, int vertex);
void removeAdjVertex(ListNode **AdjList, int vertex);
int matching(Graph g);

//////STACK///////////////////////////////////////////
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
//////////////////////////////////

int main()
{
    int Prj, Std, Mtr, i, j; //Project, Student and Mentor;
    int maxMatch;
    scanf("%d %d %d", &Std, &Prj, &Mtr);

    int np, nm; //number of projects and number of mentors

    //build graph
    Graph g;
    g.V = Prj + Std + Mtr + 2;
    g.list = (ListNode **)malloc(sizeof(ListNode *) * g.V);

    for (i = 0; i < g.V; i++)
    {
        g.list[i] = NULL;
    }

    // link source to projects
    for (i = 1; i <= Prj; i++)
    {
        insertAdjVertex(&g.list[0], i);
    }

    // link mentors to drain
    for (i = 1; i <= Mtr; i++)
    {
        int mtIndex = Std + Prj + i;
        insertAdjVertex(&g.list[mtIndex], (g.V - 1));
    }

    // for each student
    for (i = 1; i <= Std; i++)
    {
        scanf("%d %d", &np, &nm);

        // links projects preferred to student
        for (j = 0; j < np; j++)
        {
            int prjID;
            scanf("%d", &prjID);
            insertAdjVertex(&g.list[prjID], (i + Prj));
        }

        // links students to preferred mentors
        for (j = 0; j < nm; j++)
        {
            int mtrID;
            scanf("%d", &mtrID);
            insertAdjVertex(&g.list[i + Prj], (Prj + Std + mtrID));
        }
    }

    //apply Ford Fulkerson algorithm
    //use DFS or BFS to find a path
    maxMatch = matching(g);
    printf("%d\n", maxMatch);
    return 0;
}

int matching(Graph g)
{
    int matches = 0, pre[g.V], end[g.V], i;
    Stack s;
    s.head = NULL;
    s.size = 0;

    for (i = 0; i < g.V; i++)
    {
        pre[i] = -1;
        end[i] = 0;
    }

    push(&s, 0);
    ListNode **path = (ListNode **)malloc(sizeof(ListNode *) * g.V);

    while (!isEmptyStack(s))
        {
            int cur = peek(s);
            pop(&s);
            if (cur == g.V - 1)
            {
                path[matches] = NULL;
                insertAdjVertex(&(path[matches]), cur);

                while (pre[cur] != -1)
                {
                    if (cur != g.V-1 && cur != 0)
                    {
                        end[cur] = 1;
                    }
                    cur = pre[cur];
                }

                matches++;
                removeAllItemsFromStack(&s);
            }

            if (end[cur] == 0 || cur == 0)
            {
                ListNode *tmp = g.list[cur];
                while (tmp != NULL)
                {
                    push(&s, tmp->vertex);
                    pre[tmp->vertex] = cur;
                    tmp=tmp->next;
                }
            }
        }

        return matches;

}

void removeAdjVertex(ListNode **AdjList, int vertex)
{
    ListNode *temp, *preTemp;
    if (*AdjList != NULL)
    {
        // first node
        if ((*AdjList)->vertex == vertex)
        {
            temp = *AdjList;
            *AdjList = (*AdjList)->next;
            free(temp);
            return;
        }
        preTemp = *AdjList;
        temp = (*AdjList)->next;
        while (temp != NULL && temp->vertex != vertex)
        {
            preTemp = temp;
            temp = temp->next;
        }
        preTemp->next = temp->next;
        free(temp);
    }
}
void insertAdjVertex(ListNode **AdjList, int vertex)
{
    ListNode *temp;
    if (*AdjList == NULL)
    {
        *AdjList = (ListNode *)malloc(sizeof(ListNode));
        (*AdjList)->vertex = vertex;
        (*AdjList)->next = NULL;
    }
    else
    {
        temp = (ListNode *)malloc(sizeof(ListNode));
        temp->vertex = vertex;
        temp->next = *AdjList;
        *AdjList = temp;
    }
}

void push(Stack *sPtr, int vertex)
{
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->vertex = vertex;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if (sPtr == NULL || sPtr->head == NULL)
    {
        return 0;
    }
    else
    {
        StackNode *temp = sPtr->head;
        sPtr->head = sPtr->head->next;
        free(temp);
        sPtr->size--;
        return 1;
    }
}

int isEmptyStack(Stack s)
{
    if (s.size == 0)
        return 1;
    else
        return 0;
}

int peek(Stack s)
{
    return s.head->vertex;
}

void removeAllItemsFromStack(Stack *sPtr)
{
    while (pop(sPtr))
        ;
}
