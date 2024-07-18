#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
struct node
{
    char command[4096];
    struct node *next;
};
struct list
{
    int count;
    struct node *front; // holds oldest
    struct node *rear;  // holds newest
};
struct node *newnode(char *command, struct list *head,char* homedirofshell)
{
    int flag = 0;
    if (head->count == 0)
    {
        head->front=NULL;
        head->rear=NULL;
        flag = 1;
        char buffer[4096];
        FILE *file = fopen("pastevents.txt", "r");
        int line_count = 0;
        while (fgets(buffer, sizeof(buffer), file) != NULL && line_count < 16)
        {
            // Remove newline character from the end of the line
            size_t length = strlen(buffer);
            if (length > 0 && buffer[length - 1] == '\n')
            {
                buffer[length - 1] = '\0';
            }
            if (head->front == NULL)
            {
                struct node *temp = (struct node *)malloc(sizeof(struct node));
                strcpy(temp->command, buffer);
                temp->next = NULL;
                head->front = temp;
                head->rear = temp;
                head->count++;
            }
            else
            {
                if (strcmp(head->rear->command, command) != 0)
                {
                    struct node *temp = (struct node *)malloc(sizeof(struct node));
                    strcpy(temp->command, buffer);
                    head->rear->next = temp;
                    temp->next = NULL;
                    head->rear = temp;
                    head->count++;
                }
            }
        }
    }
    if (head->count < 15)
    {
        if (head->front == NULL)
        {
            struct node *temp = (struct node *)malloc(sizeof(struct node));
            strcpy(temp->command, command);
            temp->next = NULL;
            head->front = temp;
            head->rear = temp;
            head->count++;
        }
        else
        {
            if (strcmp(head->rear->command, command) != 0)
            {
                struct node *temp = (struct node *)malloc(sizeof(struct node));
                strcpy(temp->command, command);
                head->rear->next = temp;
                temp->next = NULL;
                head->rear = temp;
                head->count++;
            }
        }
    }
    else
    {
        if (strcmp(head->rear->command, command) != 0)
        {
            struct node *temp = (struct node *)malloc(sizeof(struct node));
            strcpy(temp->command, command);
            struct node *a = head->front->next;
            temp->next = NULL;
            head->rear->next = temp;
            free(head->front);
            head->front = a;
        }
    }
    char cwd[4096];
    getcwd(cwd,sizeof(cwd));
    char prev[4096];
    strcpy(prev,cwd);
    chdir(homedirofshell);
    FILE *fp = fopen("pastevents.txt", "w");
    chdir(prev);
    struct node *abc = head->front;
    while (abc != NULL)
    {
        fprintf(fp, "%s\n", abc->command);
        abc = abc->next;
    }
    fclose(fp);
    return head->front;
}