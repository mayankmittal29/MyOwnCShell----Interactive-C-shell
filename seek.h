#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#define COLOR_GREEN "\x1B[32m"
#define COLOR_BLUE "\x1B[34m"
#define COLOR_RESET "\x1B[0m"
void seek(char *commandsarray[1024], char *homedirofshell, int start, int end, char *prevdir);
void search(char *current_dir, char *searchingword, char *flag, char *homedirofshell, char *prevdir, char *pathstring);
