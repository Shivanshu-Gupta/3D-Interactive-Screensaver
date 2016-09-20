#ifndef BALLS_H
#define BALLS_H
#include "Image.h"
#include <GL/glut.h>
#include <cstdlib>
#include <cmath>
#include <ctime>
extern float PI;
enum materials{
    Plastic=1,
    Wood=2,
    Marble=3
};

class Ball{
    GLfloat radius;
    materials material;
    GLfloat mass;
    int texture_num;
    GLfloat xCenter;
    GLfloat yCenter;
    GLfloat zCenter;
    GLfloat xSpeed;
    GLfloat ySpeed;
    GLfloat zSpeed;
    GLfloat xRotBall, yRotBall, zRotBall;
    GLfloat xrot_speed, yrot_speed, zrot_speed; //adding non-random rotation speed to each ball
public:
    Ball(materials mat=Plastic) {
        static bool seeded=false;
        if(!seeded)
        {    
            srand(time(0));
            seeded=true;
        }        
        //radius=(rand()/(RAND_MAX/0.001f))+0.1;
        radius=0.15;
        material=mat;
        mass=(4*mat*PI*pow(radius,3))/3;
        xCenter=(rand()/(RAND_MAX/1.5f)) - 0.75;
        yCenter=(rand()/(RAND_MAX/1.5f)) - 0.75;
        zCenter=(rand()/(RAND_MAX/1.8f)) - 0.9;

        xSpeed=(rand()/(RAND_MAX/6.0f))-3.0f;
        ySpeed=(rand()/(RAND_MAX/6.0f))-3.0f;
        zSpeed=(rand()/(RAND_MAX/6.0f))-3.0f;
                                                                                //francaise
        xRotBall=(rand()/(RAND_MAX/20.0f));
        yRotBall=(rand()/(RAND_MAX/20.0f));
        zRotBall=(rand()/(RAND_MAX/20.0f));

        xrot_speed=(rand()/(RAND_MAX/2.0f))+1.0;
        yrot_speed=(rand()/(RAND_MAX/2.0f))+1.0;
        zrot_speed=(rand()/(RAND_MAX/2.0f))+1.0;

        texture_num =rand()%no_of_textures;
    }
    GLfloat GetRadius(){return radius;}
    void SetRadius(GLfloat r){radius = r;}
    
    GLfloat GetxCenter(){return xCenter;}
    void SetxCenter(GLfloat r){xCenter = r;}
    
    GLfloat GetyCenter(){return yCenter;}
    void SetyCenter(GLfloat r){yCenter = r;}
    
    GLfloat GetzCenter(){return zCenter;}
    void SetzCenter(GLfloat r){zCenter = r;}
    
    GLfloat GetxSpeed(){return xSpeed;}
    void SetxSpeed(GLfloat r){xSpeed = r;}
    
    GLfloat GetySpeed(){return ySpeed;}
    void SetySpeed(GLfloat r){ySpeed = r;}
    
    GLfloat GetzSpeed(){return zSpeed;}
    void SetzSpeed(GLfloat r){zSpeed = r;}

    GLfloat Getxrot_speed(){return xrot_speed;}
    GLfloat Getyrot_speed(){return yrot_speed;}
    GLfloat Getzrot_speed(){return zrot_speed;}
    
    void Setxrot_speed(GLfloat r){xrot_speed = r;}
    void Setyrot_speed(GLfloat r){yrot_speed = r;}
    void Setzrot_speed(GLfloat r){zrot_speed = r;}

    GLfloat GetxRotBall(){return xRotBall;}
    GLfloat GetyRotBall(){return yRotBall;}
    GLfloat GetzRotBall(){return zRotBall;}
    
    void SetxRotBall(GLfloat r){xRotBall = r;}
    void SetyRotBall(GLfloat r){yRotBall = r;}
    void SetzRotBall(GLfloat r){zRotBall = r;}
    
    int GetTextureNum(){return texture_num ;}
    // void Mass(){return mass;}

};

extern Ball* ball;

#endif