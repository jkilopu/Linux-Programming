#ifndef __SCOREBOARD_H
#define __SCOREBOARD_H

#include "record.h"

#define RECORD_MAX_NUM 150
#define SHOWED_MAX_NUM 8

typedef struct __scoreboard {
    Record *records;
    unsigned int size;
} * Scoreboard;

Scoreboard CreateScoreboard(int size);
FILE *OpenScoreboardFile(void);
void ReadScoreboard(Scoreboard sc);
unsigned int ShowScoreboardWithCurrentRecord(Scoreboard sc, Record cr, int y, int x);
void WriteScoreboard(Scoreboard sc, Record cr, int found);
void DestroyScoreboard(Scoreboard sc);

#endif