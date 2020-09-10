#ifndef __RECORD_H
#define __RECORD_H

#include "settings.h"
#include <stdio.h>

#define NAME_MAX_LENGTH 11
#define NUM_MAX_LENGTH 2
#define SCORE_MAX 99999
#define SCORE_MAX_LENGTH 5

typedef struct _record {
    char name[NAME_MAX_LENGTH + 1];
    unsigned int score;
} * Record;

Record CreateRecord(char *name);
void ShowRecord(Record r, unsigned int number, int y, int x);
int ReadRecord(Record r, FILE *fp);
int FindRecord(Record rs[], int num, char name[]);

#endif