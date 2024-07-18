#include "pastevents_purge.h"
void pastevents_purge(struct list *head)
{
    FILE *fp = fopen("pastevents.txt", "w");
    fclose(fp);
    struct node *start = head->front;
    while (start != NULL)
    {
        struct node *a = start;
        start = start->next;
        free(a);
    }
    head->front=NULL;
    head->rear=NULL;
    head->count=0;
    return;
}