#include<stdio.h>
#include <stdlib.h>
#include "List.h"

// Structs --------------------------------------------------------------------
typedef struct NodeObj
{
    int data;
    struct NodeObj* prev;
    struct NodeObj* next;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// Private ListObj type
typedef struct ListObj
{
    int length;
    int cursorIndex;
    Node front;
    Node back;
    Node cursor;
}ListObj;

// Constructors-Destructors ---------------------------------------------------
Node newNode(int data)
{
    Node node = malloc(sizeof(NodeObj));
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    return(node);
}

void freeNode(Node *pointerNode)
{
    if (pointerNode != NULL && *pointerNode != NULL)
    {
        free(*pointerNode);
        *pointerNode = NULL;
    }
}
List newList(void)
{ // Creates new empty list
    List L;
    L = malloc(sizeof(ListObj));
    L->cursorIndex = -1;
    L->length = 0;
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    return (L);
}
void freeList(List* pointerList)
{
    if (pointerList != NULL && *pointerList != NULL)
    {
        clear(*pointerList); // Can use clear function to empty the list
        free(*pointerList);
        *pointerList = NULL;
    }
}
// Access functions -----------------------------------------------------------
int length(List L)
{
    if (L == NULL)
    {
        printf("List Error: NULL\n");
        exit(1);
    }
    return (L->length);
}

int index(List L)
{
    if (L == NULL)
    {
        printf("List Error: NULL\n");
        exit(1);
    }
    return (L->cursorIndex);
}

int front(List L)
{
    if (L == NULL)
    {
        printf("List Error: NULL\n");
        exit(1);
    }
    return (L->front->data);
}

int back(List L)
{
    if (L == NULL)
    {
        printf("List Error: NULL\n");
        exit(1);
    }
    return (L->back->data);
}

int get(List L)
{
    if (L == NULL)
    {
        printf("List Error: NULL\n");
        exit(1);
    }
    return L->cursor->data;
}

int equals(List A, List B)
{
    if (A->length == B->length)
    {
        if (A->length == 0 && B->length == 0)
        {
            return 1;
        }
        Node temp = A->front;
        Node temp2 = B->front;
        while (temp != NULL && temp2 != NULL) // Compare both elements starting from the front
        {
            if (temp->data != temp2->data)
            {
                return 0;
            }
            temp = temp->next;   // move to next element of List A
            temp2 = temp2->next; // move to next element of List B
        }
        return 1;
    }
    else
        return 0;
}
// Manipulation procedures ----------------------------------------------------
void clear(List L)
{
    if(L == NULL)
    {
        printf("List Error: NULL\n");
        exit(1);
    }
    while (L->front != NULL) // While first element is not null, just keep deleting the first element to clear list.
    {
        deleteFront(L);
    }
}

void moveFront(List L)
{
    if(L == NULL)
    {
        printf("List Error: NULL\n");
        exit(1);
    }
    if (L != NULL)
    {
        if (L->length > 0)
        {
            L->cursor = L->front;
            L->cursorIndex = 0;
        }
    }
}
void moveBack(List L)
{
    if(L == NULL)
    {
        printf("List Error: NULL\n");
        exit(1);
    }
    if (L != NULL)
    {
        if (L->length > 0)
        {
            L->cursor = L->back;
            L->cursorIndex = L->length - 1;
        }
    }
}
void movePrev(List L)
{
    if(L == NULL)
    {
        printf("List Error: NULL\n");
        exit(1);
    }
    if (L->cursor != NULL)
    {
        if (L->cursor != L->front)
        {
            L->cursor = L->cursor->prev;
            L->cursorIndex--;
        }
        else if (L->cursor == L->front) // Adjust the new cursor if cursor happens to be front
        {
            L->cursor = NULL;
            L->cursorIndex = -1;
        }
    }
}
void moveNext(List L)
{
    if(L == NULL)
    {
        printf("List Error: NULL\n");
        exit(1);
    }
    if (L != NULL)
    {
        if (L->cursor != NULL)
        {
            if (L->cursor != L->back)
            {
                L->cursor = L->cursor->next;
                L->cursorIndex++;
            }
            else if (L->cursor->next == NULL) // Adjust the new cursor if cursor happens to be back
            {
                L->cursor = NULL;
                L->cursorIndex = -1;
            }
        }
    }
}
void prepend(List L, int data)
{
    if(L == NULL)
    {
        printf("List Error: NULL\n");
        exit(1);
    }
    if (L != NULL)
    {
        if (L->length != 0)
        {
            Node temp = newNode(data);
            L->front->prev = temp;
            temp->next = L->front;
            L->front = temp;
            L->length++;
            L->cursorIndex++;
        }
        else
        {
            Node temp = newNode(data);
            L->front = L->back = temp;
            L->length++;
        }
    }
}
void append(List L, int data)
{
    if(L == NULL)
    {
        printf("List Error: NULL\n");
        exit(1);
    }
    if (L != NULL)
    {
        if (L->length != 0)
        {
            Node temp = newNode(data);
            L->back->next = temp;
            temp->prev = L->back;
            L->back = temp;
            L->length++;
        }
        else
        {
            Node temp = newNode(data);
            L->front = L->back = temp;
            L->length++;
        }
    }
}

void insertBefore(List L, int data)
{
    if(L == NULL)
    {
        printf("List Error: NULL\n");
        exit(1);
    }
    if (L != NULL)
    {
        if (L->cursor == L->front) // Can append if theres only a single element in list.
        {
            prepend(L, data);
        }
        else
        {
            Node temp = newNode(data);
            temp->next = L->cursor;
            temp->prev = L->cursor->prev;
            L->cursor->prev->next = temp;
            L->cursor->prev = temp;
            L->length++;
            if (L->cursor != NULL)
            {
                L->cursorIndex++;
            }
        }
    }
}

void insertAfter(List L, int data)
{
    if(L == NULL)
    {
        printf("List Error: NULL\n");
        exit(1);
    }
    if (L != NULL)
    {
        if (L->cursor == L->back) // Can append if theres only a single element in list.
        {
            append(L, data);
        }
        else
        {
            Node temp = newNode(data);
            temp->prev = L->cursor;
            temp->next = L->cursor->next;
            L->cursor->next->prev = temp;
            L->cursor->next = temp;
            L->length++;
            if (L->cursor != NULL)
            {
                L->cursorIndex++;
            }
        }
    }
}
void deleteFront(List L)
{
    if(L == NULL)
    {
        printf("List Error: NULL\n");
        exit(1);
    }
    Node N= NULL;
    if (L != NULL && L != 0)
    {
        if (L->cursor == L->front)
        {
            L->cursor = NULL;
            L->cursorIndex = -1;
        }
        if (L->cursor != NULL)
        {
            L->cursorIndex--;
        }
        if(L->length > 1)
        {
            N = L->front; // Set Node to L->front for free function.
            L->front = L->front->next;
            freeNode(&N);
        }
        else
        {
            N = L->front; // Set Node to L->front for free function.
            freeNode(&N);
            L->front = NULL;
        }
        L->length--;
    }
}
void deleteBack(List L)
{
    if(L == NULL)
    {
        printf("List Error: NULL\n");
        exit(1);
    }
    Node N = NULL;
    if (L != NULL && L!= 0)
    {
        if (L->cursor == L->back)
        {
            L->cursor = NULL;
            L->cursorIndex = -1;
        }
        if (L->length > 1)
        {
            N = L->back;  // Set Node to L->back for free function.
            L->back = L->back->prev;
            L->back->next = NULL;
            freeNode(&N);
        }
        else
        {
            N = L->back;  // Set Node to L->back for free function.
            freeNode(&N);
            L->back = NULL;
        }
        L->length--;
    }
}
void delete(List L)
{
if(L == NULL)
{
printf("List Error: NULL\n");
exit(1);
}
Node N = NULL;
N = L->cursor;  // Set Node to L->cursor for free function.
if (L != NULL)
{
if (L->cursor == L->front)
{
deleteFront(L);
}
else if (L->cursor == L->back)
{
deleteBack(L);
}
else
{
L->cursor->prev->next = L->cursor->next;
L->cursor->next->prev = L->cursor->prev;
L->cursor = NULL;
L->cursorIndex = -1;
L->length--;
freeNode(&N);
}
}
}
// Other operations -----------------------------------------------------------
void printList(FILE* out, List L)
{
    if(L == NULL)
    {
        printf("List Error: NULL\n");
        exit(1);
    }
    Node N = NULL;
    if (L != NULL)
    {
        for (N = L->front; N != NULL; N = N->next)
        {
            fprintf(out,"%d ", N->data);
        }
    }
}
List copyList(List L)
{
    if(L == NULL)
    {
        printf("List Error: NULL\n");
        exit(1);
    }
    List copiedList = newList();
    Node temp = L->front;
    while (temp != NULL)
    {
        append(copiedList, temp->data);
        temp = temp->next;
    }
    copiedList->cursor = NULL;
    copiedList->cursorIndex = -1;
    return copiedList;
}
