#include "record.h"
#include "settings.h"
#include "fatal.h"
#include <ncurses.h>
#include <stdio.h>

Record *CreateScoreboard(int num)
{
    Record *sc;
    if ((sc = (Record *)malloc(sizeof(Record) * num)) == NULL)
        FatalError("Out of space!");
    for (int i = 0; i < num; i++)
        if ((sc[i] = (Record)malloc(sizeof(struct _record))) == NULL)
            FatalError("Out of space!");
    return sc;
}

void ShowRecord(Record r, int y, int x)
{
    char sNum[NUM_MAX_LENGTH + 1];
    snprintf(sNum, NUM_MAX_LENGTH + 1, "%u", r->num);
    mvaddnstr(y, x, sNum, NUM_MAX_LENGTH + 1);

    mvaddnstr(y, x + NUM_MAX_LENGTH + 1, r->name, NAME_MAX_LENGTH + 1); // +1?

    char sScore[SCORE_MAX_LENGTH + 1];
    snprintf(sScore, SCORE_MAX_LENGTH + 1, "%u", r->score);
    mvaddnstr(y, x + NUM_MAX_LENGTH + NAME_MAX_LENGTH + 2, sScore, SCORE_MAX_LENGTH + 1);
}

void ShowScoreboard(Record sc[], int num, int y, int x)
{
    for (int i = 0; i < num; i++)
        ShowRecord(sc[i], y + i, x);
}

int ReadRecord(Record r, FILE *fp)
{
    return fscanf(fp, "%u %s %u", &r->num, r->name, &r->score);
}

FILE *OpenScoreboardFile(const char *file_name)
{
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL)
        FatalError("Open failed");
    return fp;
}

int ReadScoreboard(Record sc[], FILE *fp)
{
    int num = 0;
    while (num < RECORD_MAX_NUM)
    {
        int status = ReadRecord(sc[num], fp);
        if (status != 3)
            if (status != EOF)
                FatalError("Incomplete data");
            else
                break;
        num++;
    }
    return num;
}

void DestroyScoreboard(Record sc[], int num)
{
    for (int i = 0; i < num; i++)
        free(sc[num]);
    free(sc);
}