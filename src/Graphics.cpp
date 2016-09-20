#include "Graphics.h"
#include "Balls.h"
#include "Image.h"
#include "Physics.h"

#include <unistd.h>     // Header file for sleeping.
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <pthread.h>
#include <stdio.h>
#include <GL/glut.h>


/* ascii code for the escape key */
#define ESCAPE 27
#define refresh_time 30
#define handle_error(msg) do{ perror(msg); exit(-1); }while(0)

float PI = 3.14159265358979323846f;

GLfloat xrot_speed, yrot_speed, zrot_speed; 


/* The number of our GLUT window */
int window;
int no_of_balls=5;
long ball_selected=3;
bool sel_mode=false;
/* floats for x rotation, y rotation, z rotation */
float xrot, yrot, zrot;


GLUquadric *quad;

GLfloat aspect;
GLfloat z=0.0f;
GLfloat xRotBox=0.0f, yRotBox=0.0f, zRotBall=0.0f;
Image* img;

enum MENU_ITEM
{
    ADD,
    DEL,
    INC,
    DEC,
    RAND
};
/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL(int Width, int Height)          // We call this right after our OpenGL window is created.
{
    LoadGLTextures("img/planets.bmp",0);
    LoadGLTextures("img/metal.bmp",1);
    LoadGLTextures("img/flower.bmp",2);
    LoadGLTextures("img/planets.bmp",3);
    LoadGLTextures("img/metal.bmp",4);
 
    glEnable(GL_TEXTURE_2D);

    // This Will Clear The Background Color To Black
    glClearColor(0.1f,0.1f,0.1f,0.5f);
    glClearDepth(1.0);              // Enables Clearing Of The Depth Buffer
    glEnable(GL_BLEND); //sachin
    glDepthFunc(GL_LESS);           // The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);        // Enables Depth Testing
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);    

    glShadeModel(GL_SMOOTH);        // Enables Smooth Color Shading
    
    glEnable(GL_LIGHTING);
    /* white ambient light at half intensity (rgba) */
    GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    /* super bright, full intensity diffuse light. */
    GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };

    /* position of light (x, y, z, (position of light)) */
    GLfloat lightPosition1[] = { 0.0f, 1.0f, -4.0f, 0.0f };
    GLfloat lightPosition2[] = { 0.0f, 1.0f, 4.0f, 0.0f };

    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);    
    //LightUp(amb_light);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);  // add lighting. (ambient)
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);  // add lighting. (diffuse).
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1); // set light position.
    glEnable(GL_LIGHT1);                             // turn light 1 on.

    glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight);  // add lighting. (ambient)
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight);  // add lighting. (diffuse).
    glLightfv(GL_LIGHT2, GL_POSITION, lightPosition2); // set light position.
    glEnable(GL_LIGHT2);                             // turn light 1 on.

    quad = gluNewQuadric();                                // Create A New Quadratic
    gluQuadricNormals(quad, GL_SMOOTH);                    // Generate Smooth Normals For The Quad
    gluQuadricTexture(quad, GL_TRUE);                      // Enable Texture Coords For The Quad

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);    // Set Up Sphere Mapping
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);    // Set Up Sphere Mapping    
    
    glBlendFunc(GL_SRC_ALPHA,GL_ONE); //sachin                   // Set The Blending Function For Translucency    
}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int w, int h)
{ 
    glViewport(0,0,w,h);  //Use the whole window for rendering

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (h == 0)
      return;                // To prevent divide by 0
    aspect = (GLfloat)w / (GLfloat)h;
    if (w >= h) {
        // aspect >= 1, set the height from -1 to 1, with larger width
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    } else {
        // aspect < 1, set the width to -1 to 1, with larger height
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }
    gluPerspective(45.0f,aspect,0.1f,100.0f);
    
    glMatrixMode(GL_MODELVIEW);
    //gluLookAt (0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);    
} 
void DrawBall(long k)
{
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA,GL_SRC_COLOR); //sachin                   // Set The Blending Function For Translucency    
    /*ball[k].Setxrot_speed(rand()/(RAND_MAX/2.0f)); //x_rotation                                                               //francaise
    ball[k].Setyrot_speed(rand()/(RAND_MAX/2.0f)); //y_rotation
    ball[k].Setzrot_speed(rand()/(RAND_MAX/2.0f)); //z_rotation*/
    ball[k].SetxRotBall(ball[k].GetxRotBall()+ ball[k].Getxrot_speed());
    ball[k].SetyRotBall(ball[k].GetyRotBall()+ ball[k].Getxrot_speed());
    ball[k].SetzRotBall(ball[k].GetzRotBall()+ ball[k].Getxrot_speed());
    glTranslatef(ball[k].GetxCenter(),ball[k].GetyCenter(),ball[k].GetzCenter());                     //edit 2

    glColor3f(1.0,0.4,0.6);
    glColor3f(1.0f,1.0f,1.0f);


    // changing in transformation matrix.
    // rotation about X axis
    if(!paused)
    {
       
        glRotatef(ball[k].GetxRotBall(),1.0,0.0,0.0);
        // rotation about Y axis
        glRotatef(ball[k].GetyRotBall(),0.0,1.0,0.0);
        // rotation about Z axis
        glRotatef(ball[k].GetzRotBall(),0.0,0.0,1.0);
        // scaling transfomation 
      }
    glScalef(1.0,1.0,1.0);
    // built-in (glut library) function , draw you a sphere.
    //glutSolidSphere(ball[k].GetRadius(),20,20);

    glBindTexture(GL_TEXTURE_2D, texture[ball[k].GetTextureNum()]);
    gluQuadricTexture(quad,1);
    gluSphere(quad,ball[k].GetRadius(),20,20);

}

void add_ball()
{
    no_of_balls++;
    Ball* ball_new=new Ball[no_of_balls];
    Ball temp;
    int i;
    for(i=0;i<no_of_balls-1;i++)
    {
        ball_new[i]=ball[i];
    }
    ball_new[no_of_balls-1]=temp;
    ball=ball_new;
    ball_new=NULL;
    delete ball_new;
}

void remove_ball()
{
    //no_of_balls--;
    Ball* ball_new=new Ball[no_of_balls-1];
    int i=0;
    int l=0;
    for(i=0;i<no_of_balls-1;i++)
    {
        ball_new[i]=ball[i];
    }
    ball=ball_new;
    ball_new=NULL;
    delete ball_new;
    no_of_balls--;
}

void speed_up(long k)
{
    ball[k].SetxSpeed(ball[k].GetxSpeed()*1.1);
    ball[k].SetySpeed(ball[k].GetySpeed()*1.1);
    ball[k].SetzSpeed(ball[k].GetzSpeed()*1.1);
}

void speed_down(long k)
{
    ball[k].SetxSpeed(ball[k].GetxSpeed()*0.9);
    ball[k].SetySpeed(ball[k].GetySpeed()*0.9);
    ball[k].SetzSpeed(ball[k].GetzSpeed()*0.9);    
}

void halo_ball(long k)
{
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA,GL_SRC_COLOR); //sachin                   // Set The Blending Function For Translucency    
    /*ball[k].Setxrot_speed(rand()/(RAND_MAX/2.0f)); //x_rotation                                                               //francaise
    ball[k].Setyrot_speed(rand()/(RAND_MAX/2.0f)); //y_rotation
    ball[k].Setzrot_speed(rand()/(RAND_MAX/2.0f)); //z_rotation*/
    ball[k].SetxRotBall(ball[k].GetxRotBall()+ ball[k].Getxrot_speed());
    ball[k].SetyRotBall(ball[k].GetyRotBall()+ ball[k].Getxrot_speed());
    ball[k].SetzRotBall(ball[k].GetzRotBall()+ ball[k].Getxrot_speed());
    glTranslatef(ball[k].GetxCenter(),ball[k].GetyCenter(),ball[k].GetzCenter());                     //edit 2

    glColor3f(1.0,0.4,0.6);
    glColor3f(0.0f,0.0f,0.0f);


    // changing in transformation matrix.
    // rotation about X axis
    if(!paused)
    {
       
        glRotatef(ball[k].GetxRotBall(),1.0,0.0,0.0);
        // rotation about Y axis
        glRotatef(ball[k].GetyRotBall(),0.0,1.0,0.0);
        // rotation about Z axis
        glRotatef(ball[k].GetzRotBall(),0.0,0.0,1.0);
        // scaling transfomation 
      }
    glScalef(1.0,1.0,1.0);
    // built-in (glut library) function , draw you a sphere.
    //glutSolidSphere(ball[k].GetRadius(),20,20);
    glBindTexture(GL_TEXTURE_2D, texture[ball[k].GetTextureNum()]);//P
    GLfloat sel_Light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat sel_lightPosition[] = { ball[k].GetxCenter(), ball[k].GetyCenter(), ball[k].GetzCenter(), 0.0f };

    glLightfv(GL_LIGHT3, GL_DIFFUSE, sel_Light);  // add lighting. (diffuse).
    glLightfv(GL_LIGHT3, GL_POSITION, sel_lightPosition); // set light position.
    glEnable(GL_LIGHT3);                             // turn light 1 on.
    gluQuadricTexture(quad,1);
    gluSphere(quad,ball[k].GetRadius(),20,20);
}

void DrawCube()
{
    
    //glTranslatef(0.0f,0.0f,-4.0f);                  //the camera is placed at z=4, and we have loaded identity <---wrong...as the coordinate axis are still at there pos. and translate is w.r.t. origin, not camera
    glDisable(GL_DEPTH_TEST);                   //sachin
    glBlendFunc(GL_SRC_ALPHA,GL_ONE); //sachin                   // Set The Blending Function For Translucency        
    glBindTexture(GL_TEXTURE_2D, texture[0]);            //sachin
    //glBindTexture(GL_TEXTURE_2D,0);
    GLfloat height=1.0, width=1.0, depth=1.0;
    if(aspect>=1)
        width*=aspect;
    else
        height/=aspect; 

    glBegin(GL_QUADS);
        //glColor4f(0.7f,1.0f,0.3f,0.5f);           //not required when using texture
        //Front Face
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, -height, depth);  // Bottom Right Of The Texture and Quad
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-width,  height, depth);  // Top Right Of The Texture and Quad
        glTexCoord2f(0.0f, 1.0f); glVertex3f( width,  height, depth);  // Top Left Of The Texture and Quad
        glTexCoord2f(0.0f, 0.0f); glVertex3f( width, -height, depth);  // Bottom Left Of The Texture and Quad

        // Back Face
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, -height, -depth);  // Bottom Right Of The Texture and Quad
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-width,  height, -depth);  // Top Right Of The Texture and Quad
        glTexCoord2f(0.0f, 1.0f); glVertex3f( width,  height, -depth);  // Top Left Of The Texture and Quad
        glTexCoord2f(0.0f, 0.0f); glVertex3f( width, -height, -depth);  // Bottom Left Of The Texture and Quad
        
        // Top Face
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-width,  height, -depth);  // Top Left Of The Texture and Quad
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-width,  height,  depth);  // Bottom Left Of The Texture and Quad
        glTexCoord2f(1.0f, 0.0f); glVertex3f( width,  height,  depth);  // Bottom Right Of The Texture and Quad
        glTexCoord2f(1.0f, 1.0f); glVertex3f( width,  height, -depth);  // Top Right Of The Texture and Quad
        
        // Bottom Face       
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-width, -height, -depth);  // Top Right Of The Texture and Quad
        glTexCoord2f(0.0f, 1.0f); glVertex3f( width, -height, -depth);  // Top Left Of The Texture and Quad
        glTexCoord2f(0.0f, 0.0f); glVertex3f( width, -height,  depth);  // Bottom Left Of The Texture and Quad
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, -height,  depth);  // Bottom Right Of The Texture and Quad
        
        // Right face
        glTexCoord2f(1.0f, 0.0f); glVertex3f( width, -height, -depth);  // Bottom Right Of The Texture and Quad
        glTexCoord2f(1.0f, 1.0f); glVertex3f( width,  height, -depth);  // Top Right Of The Texture and Quad
        glTexCoord2f(0.0f, 1.0f); glVertex3f( width,  height,  depth);  // Top Left Of The Texture and Quad
        glTexCoord2f(0.0f, 0.0f); glVertex3f( width, -height,  depth);  // Bottom Left Of The Texture and Quad
        
        // Left Face
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, -height, -depth);  // Bottom Left Of The Texture and Quad
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, -height,  depth);  // Bottom Right Of The Texture and Quad
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-width,  height,  depth);  // Top Right Of The Texture and Quad
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-width,  height, -depth);  // Top Left Of The Texture and Quad
    glEnd();
    glBindTexture(GL_TEXTURE_2D,0);
    glEnable(GL_DEPTH_TEST);                    //sachin

}

void DrawBackground()
{
    //glDisable(GL_DEPTH_TEST);
    GLfloat height=8*tan(22.5), width=height*aspect, depth=0.0;
    glBindTexture(GL_TEXTURE_2D,texture[0]);
    glTranslatef(0.0f,0.0f,-4.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, -height, -depth);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-width,  height, -depth);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( width,  height, -depth);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( width, -height, -depth);  // Bottom Left Of The Texture and Quad    
    glEnd();
    glBindTexture(GL_TEXTURE_2D,0);    
    //glEnable(GL_DEPTH_TEST);                    //sachin

}
void processMenuEvents(int option) {

    switch (option) {
        case ADD : break;
        case DEL : break;
        case INC : break;
        case DEC : break;
        case RAND : break;
    }
}

void CreateMenu()
{
    int menu;
    // create the menu and
    // tell glut that "processMenuEvents" will
    // handle the events
    menu = glutCreateMenu(processMenuEvents);

    //add entries to our menu
    glutAddMenuEntry("Add Ball",ADD);
    glutAddMenuEntry("Remove Ball",DEL);
    glutAddMenuEntry("Increase Speed",INC);
    glutAddMenuEntry("Decrease Speed",DEC);
    glutAddMenuEntry("Randomise Speed",RAND);

    // attach the menu to the right button
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/* The main drawing function. */
void DrawGLScene()
{
    //usleep(1000);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // Clear The Screen And The Depth Buffer
    glMatrixMode(GL_MODELVIEW);
    int check_thread;
    long k;
    //GLfloat z=-2.0;                                   //made global
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();                                   //Reset the view
    gluLookAt (0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glPushMatrix();
    DrawBackground();
    glPopMatrix();

    glTranslatef(0.0f,0.0f,z);
    glRotatef(xRotBox,0.0f,1.0f,0.0f);
    glRotatef(yRotBox,1.0f,0.0f,0.0f);
    //glRotatef(zRotBox,0.0f,0.0f,1.0f);
    glPushMatrix();                                     //save the changes to the model-view matrix made by glLookAt() 
    DrawCube();
    glPopMatrix();                                      //Load the changes

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,aspect,0.1f,100.0f);

    for(k=0;k<no_of_balls;k++)
    {
        glMatrixMode(GL_MODELVIEW);
        //glLoadIdentity();                                                   //edit2*/
        glPushMatrix();        
        //gluLookAt (0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        if(ball_selected==k && sel_mode)
            halo_ball(k);
        else
            DrawBall(k);
        glPopMatrix();
    }
    if(paused)
    {
        CreateMenu();
    }
/*    glEnable2D();
    DrawButtons();
    glDisable2D();*/
    /*GLfloat max_rad = ball[0].GetRadius();                 //not used anywhere
    for (int k = 1; k < no_of_balls; k++)
    {
        if(ball[k].GetRadius()>max_rad)
            max_rad = ball[k].GetRadius();
    }*/
    
    pthread_t threads[no_of_balls];
    for(k=0;k<no_of_balls;k++)
         collided[k]=0;
    for(k=0; k<no_of_balls; k++)
    {
            if(check_thread= pthread_create(&threads[k],NULL,calc_motion,&k))
                handle_error("thread error ");
            pthread_join(threads[k],NULL);
    } 
    glutSwapBuffers();
}


void Timer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(refresh_time, Timer, 0);
}


void mouse_click_control(int button, int state,int x, int y)
{
   // Wheel reports as button 3(scroll up) and button 4(scroll down)
   if((button == 3) || (button == 4)) // It's a wheel event
   {
        // Each wheel event reports like a button click, GLUT_DOWN then GLUT_UP
        if (state == GLUT_UP) return; // Disregard redundant GLUT_UP events
        if(button==3)
        {
            if(z< 3.0f)
                z+=1.0f;
        }
        else
        {
            if(z>-3.0f)
                z-=1.0f;
        }
    }
}

void mouse_passive_motion_control(int x, int y)
{
    usleep(100);
    int vPort[4];
    glGetIntegerv(GL_VIEWPORT, vPort);
   // cout<<vPort[2]<<' '<<vPort[3]<<'\n';
    xRotBox=360*((GLfloat)x/vPort[2]);
    yRotBox=-360*((GLfloat)y/vPort[3]);

}  
/* The function called whenever a key is pressed. */
void keyPressed(unsigned char key, int x, int y)
{
    /* avoid thrashing this procedure */
    usleep(50);
    if(key==27)
    {
        /* shut down our window */
        glutDestroyWindow(window);
                
        /* exit the program...normal termination. */
        exit(0);
    }
    else if(key=='s')
    {
        sel_mode=!sel_mode;
    }
    else if(key=='+')
    {
        add_ball();
    }
    
    if(sel_mode)
    {
        if(key==' ')
        {   
            paused=!paused;
            return;
        }
        else if(key=='n')
        {
            ball_selected=(ball_selected+1)%no_of_balls;
        }
        else if(key=='+')
        {
            add_ball();
        }
        else if(key=='-')
        {
            remove_ball();
        }
        else if(key==GLUT_KEY_UP)
        {
            speed_up(ball_selected);
        }
        else if(key==GLUT_KEY_DOWN)
        {
            speed_down(ball_selected);
        }
    }
}
void specialKeyPressed(int key, int x, int y)
{
    usleep(50);
    if(key==GLUT_KEY_F11)
    {
        glutFullScreen();
    }
}

