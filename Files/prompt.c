#include "headers.h"
void prompt(char *homedirofshell, char *display, int* flag)
{
    char username[MAX_INPUT_LENGTH];
    char sysname[MAX_INPUT_LENGTH];
    char a[MAX_INPUT_LENGTH];
    char home[] = "/home/";
    getlogin_r(username, MAX_INPUT_LENGTH);
    strcpy(a, username);
    gethostname(sysname, MAX_INPUT_LENGTH);
    strcat(home, username);
    char newcurrdir[MAX_PATH_LENGTH];
    getcwd(newcurrdir, MAX_PATH_LENGTH);
    // printf("%s\n",newcurrdir);
    if (flag == 0)
    {
        if ((newcurrdir != NULL) && (strcmp(homedirofshell, newcurrdir) == 0))
        {
            strcpy(newcurrdir, "~");
            printf("<%s@%s:%s> ", a, sysname, newcurrdir);
        }
        else if (strncmp(homedirofshell, newcurrdir, strlen(homedirofshell)) == 0)
        {
            strcpy(newcurrdir, newcurrdir + strlen(homedirofshell));
            printf("<%s@%s:~%s> ", a, sysname, newcurrdir);
        }
        else
        {
            printf("<%s@%s:~%s> ", a, sysname, newcurrdir);
        }
        fflush(stdout);
    }
    else
    {
        if ((newcurrdir != NULL) && (strcmp(homedirofshell, newcurrdir) == 0))
        {
            strcpy(newcurrdir, "~");
            printf("<%s@%s:%s %s> ", a, sysname, newcurrdir,display);
            *flag=0;
        }
        else if (strncmp(homedirofshell, newcurrdir, strlen(homedirofshell)) == 0)
        {
            strcpy(newcurrdir, newcurrdir + strlen(homedirofshell));
            printf("<%s@%s:~%s %s> ", a, sysname, newcurrdir,display);
            *flag=0;
        }
        else
        {
            printf("<%s@%s:~%s %s> ", a, sysname, newcurrdir,display);
            *flag=0;
        }
        fflush(stdout);
    }
}
