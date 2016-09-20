#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <GL/glut.h>
#include "Balls.h"

extern int no_of_balls;
//extern const int no_of_textures;
extern GLfloat aspect;
extern GLUquadric *quad;
extern int window;
extern long ball_selected;
extern bool sel_mode;
//extern GLuint texture[no_of_textures];
void InitGL(int Width, int Height);          // We call this right after our OpenGL window is created.
void ReSizeGLScene(int w, int h);
void DrawCube();
void DrawBackground();
void DrawGLScene();
void Timer(int value);
void mouse_click_control(int button, int state,int x, int y);
void mouse_passive_motion_control(int x, int y);
void keyPressed(unsigned char key, int x, int y);
void specialKeyPressed(int key, int x, int y);
void add_ball();
void remove_ball();
#endif