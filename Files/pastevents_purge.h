#include<stdio.h>
#include<stdlib.h>
#ifndef _PASTEVENTS_PURGE_H
#define _PASTEVENTS_PURGE_H
struct node
{
    char command[4096];
    struct node *next;
};
struct list
{
    int count;
    struct node *front;
    struct node* rear;
};
void pastevents_purge(struct list* head);
#endif