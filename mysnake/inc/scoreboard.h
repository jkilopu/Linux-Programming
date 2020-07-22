#ifndef __SCOREBOARD_H
#define __SCOREBOARD_H

#include "record.h"

#define RECORD_MAX_NUM 10

typedef struct __scoreboard {
    Record *records;
    unsigned int size;
} * Scoreboard;

Scoreboard CreateScoreboard(int size);
FILE *OpenScoreboardFile(const char *file_name);
void ReadScoreboard(Scoreboard sc);
unsigned int ShowScoreboardWithCurrentRecord(Scoreboard sc, Record cr, int y, int x);
void DestroyScoreboard(Scoreboard sc);

#endif