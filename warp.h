#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<dirent.h>
void warp(char *commandsarray[1024], char *cwd,int start,int end,char* prevdir);
