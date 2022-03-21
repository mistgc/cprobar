#ifndef _BAR_H_
#define _BAR_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>

typedef struct Termsize{
	int row;
	int col;
}Termsize;

struct Termsize getTermSize();
void programBar(char* info, unsigned long block, unsigned long total);
void freeProgramBar();
#endif//_BAR_H_
