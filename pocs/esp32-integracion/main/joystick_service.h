

#ifndef JOYSTICK_SERVICE_H
#define JOYSTICK_SERVICE_H


#include <stdio.h>

void joystick_initialize();

void joystick_get_reading(float * read_x , float * read_y);

#endif