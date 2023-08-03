

#ifndef JOYSTICK_SERVICE_H
#define JOYSTICK_SERVICE_H

#define READING_MAX 1
#define READING_MIN -1
#define READING_NEUTRAL 0


#include <stdio.h>

void joystick_initialize();

void joystick_get_reading(float * read_x , float * read_y);

#endif