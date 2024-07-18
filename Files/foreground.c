#include "foreground.h"
void foreground(char *commandsarray[1024], char *homedirofshell, int no_of_commands, char *prevdir, char *set_of_commands2, struct list *head, struct log *top, struct log *acti)
{
    int child = fork();
    if (child == 0)
    {

        if (strcmp(commandsarray[0], "warp") == 0)
        {
            warp(commandsarray, homedirofshell, 0, no_of_commands, prevdir);
            head->front = newnode(set_of_commands2, head, homedirofshell);
        }
        else if (strcmp(commandsarray[0], "peek") == 0)
        {
            peek(commandsarray, homedirofshell, 0, no_of_commands, prevdir);
            head->front = newnode(set_of_commands2, head, homedirofshell);
        }
        else if ((strcmp(commandsarray[0], "pastevents") == 0) && (no_of_commands == 1))
        {
            pastevents(head);
        }
        else if ((strcmp(commandsarray[0], "pastevents") == 0) && (no_of_commands == 2))
        {
            pastevents_purge(head);
        }
        else if ((strcmp(commandsarray[0], "pastevents") == 0) && (no_of_commands == 3))
        {
            pastevents_execute(commandsarray[2], head, homedirofshell, prevdir, top, acti);
        }
        else if (strcmp(commandsarray[0], "seek") == 0)
        {
            seek(commandsarray, homedirofshell, 0, no_of_commands, prevdir);
            head->front = newnode(set_of_commands2, head, homedirofshell);
        }
        else if (strcmp(commandsarray[0], "proclore") == 0)
        {
            proclore(commandsarray, 0, no_of_commands, homedirofshell);
            head->front = newnode(set_of_commands2, head, homedirofshell);
        }
        else if (strcmp(commandsarray[0], "iMan") == 0)
        {
            manpage(commandsarray);
            head->front = newnode(set_of_commands2, head, homedirofshell);
        }
        else if (strcmp(commandsarray[0], "activities") == 0)
        {
            activities(acti);
            head->front = newnode(set_of_commands2, head, homedirofshell);
        }
        else if (strcmp(commandsarray[0], "ping") == 0)
        {
            signalsend(commandsarray, 0, no_of_commands, homedirofshell, top);
            head->front = newnode(set_of_commands2, head, homedirofshell);
        }
        else if (strcmp(commandsarray[0], "fg") == 0)
        {
            fg(commandsarray, acti);
            head->front = newnode(set_of_commands2, head, homedirofshell);
        }
        else if (strcmp(commandsarray[0], "bg") == 0)
        {
            bg(commandsarray, acti);
            head->front = newnode(set_of_commands2, head, homedirofshell);
        }
        else if (strcmp(commandsarray[0], "neonate") == 0)
        {
            neonate(commandsarray);
            head->front = newnode(set_of_commands2, head, homedirofshell);
        }
    }else if (child>0){
        waitpid(child,NULL,WUNTRACED);
    }
    return;
}