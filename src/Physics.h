#ifndef PHYSICS_H
#define PHYSICS_H

#include "Graphics.h"
#include <GL/glut.h>

//extern bool paused;
//extern const int no_of_balls;
extern bool* collided;
extern bool paused;
extern bool* pause_array;
void *calc_motion(void *ball_no);

#endif