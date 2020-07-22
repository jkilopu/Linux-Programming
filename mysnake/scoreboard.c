#include "scoreboard.h"
#include "fatal.h"
#include <stdlib.h>
#include <stdbool.h>

Scoreboard CreateScoreboard(int size)
{
    Scoreboard sc;
    if ((sc = (Scoreboard)malloc(sizeof(struct __scoreboard))) == NULL)
        FatalError("Out of space!");
    Record *rs;
    if ((rs = (Record *)malloc(sizeof(Record) * size)) == NULL)
        FatalError("Out of space!");
    for (int i = 0; i < size; i++)
        if ((rs[i] = (Record)malloc(sizeof(struct _record))) == NULL)
            FatalError("Out of space!");
    sc->records = rs;
    sc->size = size;
    return sc;
}

FILE *OpenScoreboardFile(const char *file_name)
{
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL)
        FatalError("Open failed");
    return fp;
}

void ReadScoreboard(Scoreboard sc)
{
    FILE *fp_sc_r = OpenScoreboardFile("score.txt");;
    int size = 0;
    while (size < RECORD_MAX_NUM)
    {
        int status = ReadRecord(sc->records[size], fp_sc_r);
        if (status != 2)
            if (status != EOF)
                FatalError("Incomplete data");
            else
                break;
        size++;
    }
    sc->size = size;
    fclose(fp_sc_r);
}

unsigned int ShowScoreboardWithCurrentRecord(Scoreboard sc, Record cr, int y, int x)
{
    bool showed = false;
    unsigned int number = 0;
    for (int i = 0; i < sc->size; i++)
    {
        if (!showed && cr->score > sc->records[i]->score)
        {
            number = i + 1;
            ShowRecord(cr, number, y + i, x);
            showed = true;
        }
        ShowRecord(sc->records[i], i + 1 + showed, y + i + showed, x);
    }
    if (!showed)
    {
        number = sc->size + 1;
        ShowRecord(cr, number, y + sc->size, x);
    }
    return number;
}

void DestroyScoreboard(Scoreboard sc)
{
    for (int i = 0; i < sc->size; i++)
        free(sc->records[i]);
    free(sc->records);
    free(sc);
}