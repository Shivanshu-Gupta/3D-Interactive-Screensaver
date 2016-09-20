#include "Physics.h"
#include "Balls.h"
#include "Graphics.h"
#include <pthread.h>
#include <stdio.h>
#include <cmath>
using namespace std;

GLfloat wind_velocity_x=0.0;
GLfloat wind_velocity_y=0.0;

bool* collided=new bool[no_of_balls];
bool paused=0;
bool* pause_array=new bool[no_of_balls];

pthread_mutex_t lock;

// Ball ball;
void *calc_motion(void *ball_no)
{
    long *n= (long *)ball_no ;
    long k=*n;
    GLfloat dist,xdist,ydist,zdist, vrel_x, vrel_y,vrel_z;
    GLfloat dotProduct, collisionScale, xCollision,yCollision,zCollision;
    bool xCollided=0, yCollided=0,zCollided=0;
    //pthread_mutex_lock(&lock);
    GLfloat xWall=1.0, yWall=1.0,zWall=1.0;
    GLfloat temp;
    //pthread_mutex_lock(&lock);
    if(aspect>=1.0)
        xWall*=aspect;
    else
        yWall/=aspect;
    
    if((xWall-ball[k].GetxCenter()-ball[k].GetRadius())<=0.03)
    {   
        temp = ball[k].GetxSpeed()*(-1);
        ball[k].SetxSpeed(temp);
        xCollided=1;
        if(wind_velocity_x<=0)
        {
            temp = ball[k].GetxCenter()+ 0.01*(ball[k].GetxSpeed()+wind_velocity_x);
            ball[k].SetxCenter(temp);
        }
    }
    else if((ball[k].GetxCenter()-ball[k].GetRadius()+xWall)<=0.03)
    {
        temp = ball[k].GetxSpeed()*(-1);
        ball[k].SetxSpeed(temp);
        xCollided=1;
        if(wind_velocity_x>=0)
            {
                temp = ball[k].GetxCenter()+ 0.01*(ball[k].GetxSpeed()+wind_velocity_x);
                ball[k].SetxCenter(temp); 
            }
    } 

    if((yWall-ball[k].GetyCenter()-ball[k].GetRadius())<=0.03)
    {
        temp = ball[k].GetySpeed()*(-1);
        ball[k].SetySpeed(temp);
        yCollided=1;
        if(wind_velocity_y<=0)
        {
            temp =  ball[k].GetyCenter() + 0.01*(ball[k].GetySpeed()+wind_velocity_y);
            ball[k].SetyCenter(temp);            
        }
    }
    else if((ball[k].GetyCenter()-ball[k].GetRadius()+yWall)<=0.03)
    {
        temp = ball[k].GetySpeed()*(-1);
        ball[k].SetySpeed(temp);
        yCollided=1;
        if(wind_velocity_y>=0)
        {
            temp = ball[k].GetyCenter() + 0.01*(ball[k].GetySpeed()+wind_velocity_y);
            ball[k].SetyCenter(temp);            
        }
    }    
    if((zWall-ball[k].GetzCenter()-ball[k].GetRadius())<=0.03)
    {
        temp = ball[k].GetzSpeed()*(-1);
        ball[k].SetzSpeed(temp);
        zCollided=1;
        //if(wind_velocity_y<=0)
        //ball[k].zCenter+=0.01*ball[k].zSpeed;            
    }
    else if((ball[k].GetzCenter()-ball[k].GetRadius()+zWall)<=0.03)
    {
        temp = ball[k].GetzSpeed()*(-1);
        ball[k].SetzSpeed(temp);
        zCollided=1;
        //if(wind_velocity_y>=0)
        //ball[k].zCenter+=0.01*ball[k].zSpeed;
    }     

    if(!paused){
    //  mouse_control();
        if(!pause_array[k])
        {
            if(!(ball_selected==k) || !sel_mode)
            {
                if(!xCollided)
                {
                    //if(wind)t
                    temp = ball[k].GetxCenter() + 0.01*(ball[k].GetxSpeed() +wind_velocity_x);
                    ball[k].SetxCenter(temp);
                }
                if(!yCollided)
                {
                    temp = ball[k].GetyCenter()+ 0.01*(ball[k].GetySpeed()+wind_velocity_y);
                    ball[k].SetyCenter(temp);
                }
                temp = ball[k].GetzCenter()+ 0.01*ball[k].GetzSpeed();
                ball[k].SetzCenter(temp);
            }
        }   
    }
    //ball[k].xSpeed=(ball[k].yCenter/2);                   //to make the balls go in circles
    //ball[k].ySpeed=-(ball[k].xCenter/2);

    pthread_mutex_lock(&lock);
    int i;
    if(!collided[k])
    {
        for(i=0; i<no_of_balls;i++)
        {
            xdist=ball[k].GetxCenter()-ball[i].GetxCenter();
            ydist=ball[k].GetyCenter()-ball[i].GetyCenter();
            zdist=ball[k].GetzCenter()-ball[i].GetzCenter();
            dist=sqrt(pow(xdist,2)+pow(ydist,2)+pow(zdist,2));
            if(dist<=ball[k].GetRadius()+ball[i].GetRadius() && i!=k)
            {   
                vrel_x=ball[i].GetxSpeed()-ball[k].GetxSpeed();
                vrel_y=ball[i].GetySpeed()-ball[k].GetySpeed();
                //vrel_z=0.0f;
                vrel_z=ball[i].GetzSpeed()-ball[k].GetzSpeed();
                dotProduct = xdist*vrel_x + ydist*vrel_y + zdist*vrel_z;
                if(dotProduct>0)
                { 
                    collisionScale = dotProduct/(dist*dist);
                    xCollision=xdist*collisionScale;
                    yCollision=ydist*collisionScale;
                    zCollision=zdist*collisionScale;

                    temp = ball[k].GetxSpeed()+ xCollision;      ball[k].SetxSpeed(temp);
                    temp = ball[k].GetySpeed()+ yCollision;      ball[k].SetySpeed(temp);
                    temp = ball[k].GetzSpeed()+ zCollision;      ball[k].SetzSpeed(temp);

                    ball[i].SetxSpeed(ball[k].GetxSpeed()- xCollision);
                    ball[i].SetySpeed(ball[k].GetySpeed()- yCollision);
                    ball[i].SetzSpeed(ball[k].GetzSpeed()- zCollision);

                }

                collided[k]=1;
                collided[i]=1; 
                break;    
            }
        }   
    }
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}