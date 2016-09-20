#include "Image.h"
#include "Graphics.h"
#include <GL/glut.h>
#include <stdio.h>
//#include <fstream>
using namespace std;

//const int no_of_textures=5;
GLuint texture[no_of_textures];

Image::Image(const char *filename) {
    FILE *file;
    unsigned long size;                 // size of the image in bytes.
    unsigned long i;                    // standard counter.
    unsigned short int planes;          // number of planes in image (must be 1) 
    unsigned short int bpp;             // number of bits per pixel (must be 24)
    char temp;                          // temporary color storage for bgr-rgb conversion.

    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL)
    {
    printf("File Not Found : %s\n",filename);
    exit(0);
    }
    
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);

    // read the width
    if ((i = fread(&sizeX, 4, 1, file)) != 1) {
    printf("Error reading width from %s.\n", filename);
    exit(0);
    }
    printf("Width of %s: %lu\n", filename, sizeX);
    
    // read the height 
    if ((i = fread(&sizeY, 4, 1, file)) != 1) {
    printf("Error reading height from %s.\n", filename);
    exit(0);
    }
    printf("Height of %s: %lu\n", filename, sizeY);
    
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = sizeX * sizeY * 3;

    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
    printf("Error reading planes from %s.\n", filename);
    exit(0);
    }
    if (planes != 1) {
    printf("Planes from %s is not 1: %u\n", filename, planes);
    exit(0);
    }

    // read the bpp
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
    printf("Error reading bpp from %s.\n", filename);
    exit(0);
    }
    if (bpp != 24) {
    printf("Bpp from %s is not 24: %u\n", filename, bpp);
    exit(0);
    }
    
    // seek past the rest of the bitmap header.
    fseek(file, 24, SEEK_CUR);

    // read the data. 
    data = (char *) malloc(size);
    if (data == NULL) {
    printf("Error allocating memory for color-corrected image data");
    exit(0);   
    }

    if ((i = fread(data, size, 1, file)) != 1) {
    printf("Error reading image data from %s.\n", filename);
    exit(0);
    }

    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
    temp = data[i];
    data[i] = data[i+2];
    data[i+2] = temp;
    }
    
    // we're done.
} 

// Load Bitmaps And Convert To Textures
void LoadGLTextures(string path, int k) { 
    // Load Texture
    Image *image = new Image(path.c_str());
    
    // // allocate space for texture
    // image = (Image *) malloc(sizeof(Image));
    // if (image == NULL) {
    // printf("Error allocating space for image");
    // exit(0);
    // }
    // if (!ImageLoad(path.c_str(), image)) {
    // exit(1);
    // }        
    
    // Create Texture   
    glGenTextures(no_of_textures, &texture[k]);
    glBindTexture(GL_TEXTURE_2D, texture[k]);   // 2d texture (x and y size)

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture

    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image->sizeX, image->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
    free(image);
};
