#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<dirent.h>
#include<fcntl.h>
#define COLOR_GREEN "\x1B[32m"
#define COLOR_BLUE "\x1B[34m"
#define COLOR_WHITE "\x1B[37m"
#define COLOR_RESET "\x1B[0m"
#ifndef _PEEK_H_
#define _PEEK_H_
void peek(char *commandsarray[1024], char *homedirofshell, int start, int end, char *prevdir);
int compare_strings(const void *a, const void *b);
void hidden(char *directory);
void nothidden(char *directory);
void descriptionhidden(char * directory);
void descriptionnothidden(char* directory);
#endif
