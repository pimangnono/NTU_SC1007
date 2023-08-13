#include <stdio.h>
#include <stdlib.h>

typedef struct _arraynode
{
    int *itemArray;
    int sizeArray;
    struct _arraynode *next;
}ArrayNode;

typedef struct _arraylist{
   int size; //the size of a possible sequence
   ArrayNode *head;
} ArrayList;

typedef struct _listnode
{
    int item;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int sum; //the number of possible sequences
   int size;
   ListNode *head;
} LinkedList;

// You should not change the prototypes of these functions
//////LinkedList///////////////////////////////////////////
int insertNode(LinkedList *ll, int index, int coin);
int removeNode(LinkedList *ll, int index);
ListNode *findNode(LinkedList ll, int index);
void removeAllItems(LinkedList *ll);
///////////////////////////////////////////////////

void sumToC(LinkedList* ll, int C, ArrayList* al);
int main()
{
    int C;
    printf("Enter a number:\n");
    scanf("%d",&C);

    LinkedList ll;
    ll.head = NULL;
    ll.sum = 0;
    ll.size = 0;
    ArrayList al;
    al.head = NULL;
    al.size = 0;

    sumToC(&ll,C,&al);
    ArrayNode* temp;
    int i,j;
    temp = al.head;
    for(i=0;i<al.size;i++){
        for(j=0;j<temp->sizeArray;j++)
            printf(" %d ",temp->itemArray[j]);
        printf("\n");
        temp = temp->next;
    }

    return 0;
}

///////////////////////////////////////////////////////
int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size)
		return 0;

        if (index == 0){
		cur = ll->head;
		ll->head = (ListNode*) malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->sum += value;
		ll->size++;
		return 1;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(*ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->sum += value;
		ll->size++;
		return 1;
	}

	return 0;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index > ll->size)
		return 0;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		ll->sum -= ll->head->item;
		free(ll->head);
		ll->head = cur;
		ll->size--;
		return 1;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(*ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return 0;

		cur = pre->next;
		ll->sum -= cur->item;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 1;
	}

	return 0;
}

ListNode *findNode(LinkedList ll, int index){

	ListNode *temp;

	if (index < 0 || index >= ll.size)
		return NULL;

	temp = ll.head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
	ll->sum =0;
}

void sumToC(LinkedList* ll, int C, ArrayList* al)
{
   int index = ll->size, reducedNum = C - ll->sum, prev;
   // base condition
   if (reducedNum < 0) return;

   // combination found
   if (reducedNum == 0)
   {
    // Check if the linked list contains distinct elements
    int isDistinct = 1;
    ListNode *cur1 = ll->head;
    while (cur1 != NULL && isDistinct)
    {
        ListNode *cur2 = cur1->next;
        while (cur2 != NULL && isDistinct)
        {
            if (cur1->item == cur2->item)
            {
                isDistinct = 0;
            }
            cur2 = cur2->next;
        }
        cur1 = cur1->next;
    }

    if (isDistinct)
    {
           ListNode *cur = ll->head;
           ArrayNode *newNode = malloc(sizeof(ArrayNode));
           newNode->sizeArray = ll->size;
           newNode->itemArray = malloc(sizeof(int) * newNode->sizeArray);
           newNode->next = NULL;
           for (int i = 0; i < newNode->sizeArray; i++)
           {
               newNode->itemArray[i] = cur->item;
               cur = cur->next;
           }

           if (al->size == 0) {
               al->head = newNode;
               al->size++;
            } else {
               ArrayNode *lastNode = al->head;
               while (lastNode->next != NULL) {
                   lastNode = lastNode->next;
               }
               lastNode->next = newNode;
               al->size++;
            }


    }

           return;


   }

   // find previous number stored in ll
   if (index == 0) prev = 1;
   else {
       ListNode *tmp = findNode(*ll, index - 1);
       prev = tmp->item;
   }

   for (int i = prev; i <= reducedNum; i++)
   {
       // add the number to the linked list
       insertNode(ll, index, i);

       // recurse to find the rest of the combination
       sumToC(ll, C, al);

       // remove the added number from the linked list
       removeNode(ll, index);
   }
}

