#ifndef __GAME_H
#define __GAME_H

void setup(void);
void start(void);
int set_ticker(int n_msecs);
void DrawBoundary(void);
void DetactAndMove(int signum);
void Restart(void);
void wrapup(void);

#endif