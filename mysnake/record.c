#include "record.h"
#include "scoreboard.h"
#include "settings.h"
#include "fatal.h"
#include <ncurses.h>
#include <stdio.h>
#include <string.h>

Record CreateRecord(char *name)
{
    Record new_record;
    if ((new_record = (Record) malloc(sizeof(struct _record))) == NULL)
        FatalError("Out of space!");
    strncpy(new_record->name, name, NAME_MAX_LENGTH + 1);
    new_record->score = 0;
    return new_record;
}

void ShowRecord(Record r, unsigned int number, int y, int x)
{
    char sNum[NUM_MAX_LENGTH + 1];
    snprintf(sNum, NUM_MAX_LENGTH + 1, "%u", number);
    mvaddnstr(y, x, "        ", NUM_MAX_LENGTH + 1);
    mvaddnstr(y, x, sNum, NUM_MAX_LENGTH + 1);

    mvaddnstr(y, x + NUM_MAX_LENGTH + 1, "                        ", NAME_MAX_LENGTH + 1);
    mvaddnstr(y, x + NUM_MAX_LENGTH + 1, r->name, NAME_MAX_LENGTH + 1); // +1?

    char sScore[SCORE_MAX_LENGTH + 1];
    snprintf(sScore, SCORE_MAX_LENGTH + 1, "%u", r->score);
    mvaddnstr(y, x + NUM_MAX_LENGTH + NAME_MAX_LENGTH + 2, "                ", SCORE_MAX_LENGTH + 1);
    mvaddnstr(y, x + NUM_MAX_LENGTH + NAME_MAX_LENGTH + 2, sScore, SCORE_MAX_LENGTH + 1);
}

int ReadRecord(Record r, FILE *fp)
{
    return (fp == NULL) ? EOF : fscanf(fp, "%s %u", r->name, &r->score);
}

int FindRecord(Record rs[], int num, char name[])
{
    for (int i = 0; i < num; i++)
    {
        if (strcmp(rs[i]->name, name) == 0)
            return i;
    }
    return -1;
}