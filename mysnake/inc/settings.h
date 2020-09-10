#ifndef __SETTINGS_H
#define __SETTINGS_H

#define DEFAULT_SPEED 100
#define BLANK ' '
#define WALL '#'
#define INITIAL_X 10
#define INITIAL_Y 10
#define INITIAL_DIRECTION_X 1
#define INITIAL_DIRECTION_Y 0

/* Can't have brackets wrapped */
#define INTERFACE_SCR_RATIO_Y 3 / 4
#define INTERFACE_SCR_RATIO_X 2 / 3

#define RECORD_1ST_X(RIGHT_BOUNDARY) RIGHT_BOUNDARY + 5
#define RECORD_1ST_Y 5

typedef struct _interface
{
    int lower_boundary;
    int right_boundary;
} Interface;

#endif