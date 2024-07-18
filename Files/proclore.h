#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAX_BUFFER_SIZE 4096
typedef struct {
    char status;
    int vm;
    int groupid;
    int pid;
} ProcessInfo;
void proclore(char *commandsarray[1024],int start, int end,char* homedirofshell);
void printinfo(int pid,char* homedirofshell);
void subtract_substring_from_start(char *string, const char *substring);
