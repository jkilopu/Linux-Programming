#ifndef __RECORD_H
#define __RECORD_H

#include "settings.h"
#include <stdio.h>

#define NAME_MAX_LENGTH 11
#define NUM_MAX_LENGTH 2
#define SCORE_MAX_LENGTH 11

typedef struct _record {
    unsigned int num;
    char name[NAME_MAX_LENGTH + 1];
    unsigned int score;
} * Record;

Record *CreateScoreboard(int num);
void ShowRecord(Record r, int y, int x);
void ShowScoreboard(Record sc[], int num, int y, int x);
int ReadRecord(Record r, FILE *fp);
FILE *OpenScoreboardFile(const char *file_name);
int ReadScoreboard(Record sc[], FILE *fp);
void DestroyScoreboard(Record sc[], int num);

#endif