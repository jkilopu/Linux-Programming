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

FILE *OpenScoreboardFile(void)
{
    FILE *fp = fopen("score.txt", "r");
    return fp;
}

void ReadScoreboard(Scoreboard sc)
{
    FILE *fp_sc_r = OpenScoreboardFile();
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
    if (fp_sc_r != NULL)
        fclose(fp_sc_r);
}

/* 遍历后全部重新打印 */
unsigned int ShowScoreboardWithCurrentRecord(Scoreboard sc, Record cr, int y, int x)
{
    bool showed = false;
    unsigned int i, number = 0;
    for (i = 0; i < sc->size; i++)
    {
        if (!showed && cr->score > sc->records[i]->score)
        {
            number = i + 1;
            if (i < SHOWED_MAX_NUM)
                ShowRecord(cr, number, y + i, x);
            showed = true;
        }
        if (i + showed < SHOWED_MAX_NUM)
            ShowRecord(sc->records[i], i + 1 + showed, y + i + showed, x);
    }
    if (!showed)
    {
        number = i + 1;
        if (i < SHOWED_MAX_NUM)
            ShowRecord(cr, number, y + i, x);
    }
    return number;
}

/* 1. 逻辑有些复杂（为了保持有序性、以及指定的一些规则）
 * 2. 完全覆盖之前的文件内容
 * 3. 没有加密
 * 4. 效率还好吧(Ω(n))
 */
void WriteScoreboard(Scoreboard sc, Record cr, int found)
{
    if (sc->size > RECORD_MAX_NUM)
        FatalError("Records are full");
    FILE *fp_sc_w = fopen("score.txt", "w");
    bool written = false;
    for (int i = 0; i < sc->size; i++)
    {
        /* 只写一次 && 合适的条件（原来没有记录 || 该记录比原记录大） && 合适的位置 */
        if (!written && (found == -1 || cr->score > sc->records[found]->score ) && cr->score > sc->records[i]->score)
        {
            fprintf(fp_sc_w, "%s %u\n", cr->name, cr->score);
            written = true;
        }
        if (i != found || cr->score <= sc->records[found]->score)
            fprintf(fp_sc_w, "%s %u\n", sc->records[i]->name, sc->records[i]->score);
    }
    if (!written && found == -1)
        fprintf(fp_sc_w, "%s %u\n", cr->name, cr->score);
    fclose(fp_sc_w);
}

void DestroyScoreboard(Scoreboard sc)
{
    for (int i = 0; i < sc->size; i++)
        free(sc->records[i]);
    free(sc->records);
    free(sc);
}