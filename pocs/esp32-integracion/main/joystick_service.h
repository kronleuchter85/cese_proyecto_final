

#ifndef JOYSTICK_SERVICE_H
#define JOYSTICK_SERVICE_H


#include <stdio.h>


#define JOYSTICK_READING_MAX 1
#define JOYSTICK_READING_MIN -1
#define JOYSTICK_READING_NEUTRAL 0


void joystick_initialize();

void joystick_get_reading(float * read_x , float * read_y);

#endif