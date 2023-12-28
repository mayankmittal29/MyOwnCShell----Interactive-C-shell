#include<stdio.h>
#include<stdlib.h>
#ifndef _PASTEVENTS_H
#define _PASTEVENTS_H
struct node
{
    char command[4096];
    struct node *next;
};
struct list
{
    int count;
    struct node *front;
};
void pastevents(struct list* head);
#endif