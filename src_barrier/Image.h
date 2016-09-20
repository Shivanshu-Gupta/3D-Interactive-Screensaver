#ifndef IMAGE_H
#define IMAGE_H
#include <string>
#include <GL/glut.h>
using namespace std;
/* Image type - contains height, width, and data */
struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
    Image(const char *filename);    
    void SetSizeX(unsigned long i){sizeX = i;}
    unsigned long GetSizeX(unsigned long i){return sizeX;}
    unsigned long GetSizeY(unsigned long i){return sizeY;}
    void SetSizeY(unsigned long i){sizeY = i;}
};
void LoadGLTextures(string path, int k);    

const int no_of_textures=5;
extern GLuint texture[];

#endif