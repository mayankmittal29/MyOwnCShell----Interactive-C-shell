#include "pastevents.h"
void pastevents(struct list *head)
{
    FILE *fp = fopen("pastevents.txt", "r");
    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), fp))
    {
        printf("%s", buffer);
    }
    fclose(fp);
    return;
}