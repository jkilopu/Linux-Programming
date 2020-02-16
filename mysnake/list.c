#include "list.h"
#include "fatal.h"
void Add(List *pList, ElementType y, ElementType x)
{
    Node *p;
    //add to linked-list
    p = (Node *)malloc(sizeof(Node));
    p->y = y, p->x = x;
    p->next = NULL;
    //attach
    if (pList->head)
    {
        pList->tail->next = p;
        pList->tail = p;
    }
    else
    {
        pList->head = p;
        pList->tail = pList->head;
    }
}
void InsertHead(List *plist, ElementType y, ElementType x)
{
    Node *p = (Node *)malloc(sizeof(Node));
    if (p == NULL)
        FatalError("Out of space!");
    p->y = y, p->x = x;
    p->next = plist->head;
    if (plist->head == NULL)
        plist->tail = p; // 设置尾巴
    plist->head = p;
}
void DeleteTail(List *plist)
{
    Node *p = plist->head;
    while (p->next != plist->tail)
        p = p->next;
    free(p->next);
    p->next = NULL;
    plist->tail = p;
}
// void Delete(List *pList, ElementType number)
// {
//     Node *p, *q;
//     for (q = NULL, p = pList->head; p; q = p, p = p->next) //这里有q=p啊啊
//     {
//         if (p->value == number)
//         {
//             if (q)
//                 q->next = p->next; //不会出现野指针
//             else
//                 pList->head = p->next;
//             free(p);
//             break;
//         }
//     }
// }
void Clear(List *pList)
{
    Node *p, *q;
    for (p = pList->head; p; p = q)
    {
        q = p->next;
        free(p);
    }
}