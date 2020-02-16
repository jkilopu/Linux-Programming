#ifndef _LIST_h
#define _LIST_h

#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;
typedef struct _node
{
    ElementType x, y;
    struct _node *next;
} Node;
typedef struct _list
{
    Node *head;
    Node *tail;
} List;
void Add(List *pList, ElementType y, ElementType x);
void InsertHead(List *plist, ElementType y, ElementType x);
void DeleteTail(List *plist);
void Clear(List *pList);

#endif