#include "Graphics.h"
#include "Balls.h"
#include "Image.h"
#include "Physics.h"

#include <GL/glut.h>
#include <stdio.h>
using namespace std;

void InitGL(int Width, int Height);          // We call this right after our OpenGL window is created.
void ReSizeGLScene(int w, int h);
void DrawCube();
void DrawBackground();
void DrawGLScene();
void Timer(int value);
void mouse_click_control(int button, int state,int x, int y);
void mouse_passive_motion_control(int x, int y);
void keyPressed(unsigned char key, int x, int y);

int main(int argc, char **argv)
{
    /* Initialize GLUT state - glut will take any command line arguments that pertain to it or
    X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */
    glutInit(&argc, argv);
    
    /* Select type of Display mode:
    Double buffer
    RGBA color
    Alpha components supported
    Depth buffer */
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    
    /* get a 640 x 480 window */
    glutInitWindowSize(1360,768);
    
    /* the window starts at the upper left corner of the screen */
    glutInitWindowPosition(0, 0);
    
    /* Open a window */
    window = glutCreateWindow("Assignment 1 | Design Practices");
    /* Register the function to do all our OpenGL drawing. */
    glutDisplayFunc(&DrawGLScene);
    
    /* Go fullscreen.  This is as soon as possible. */
    glutFullScreen();
    
    /* Even if there are no events, redraw our gl scudents disturbed the LAN connections and
created routing loopsene. */
    //glutIdleFunc(&DrawGLScene);
    glutTimerFunc(0,Timer,0);
    
    /* Register the function called when our window is resized. */
    glutReshapeFunc(&ReSizeGLScene);
    
    /* Register the function called when a ascii key is pressed. */
    glutKeyboardFunc(&keyPressed);

    /* Register the function called when a special key is pressed. */
    glutSpecialFunc(&specialKeyPressed);

     /* Register the function called when the mouse is pressed. */
    glutMouseFunc(&mouse_click_control);

    /*Register the function called when the mouse is moved with being clicked*/
    glutPassiveMotionFunc(&mouse_passive_motion_control);
    
    /* Initialize our window. */
    InitGL(1360, 768);
    
    /* Start Event Processing Engine */
    glutMainLoop();
    
    return 1;
}
