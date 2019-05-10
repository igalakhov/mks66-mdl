#ifndef WORK_01_LINE_SETTINGS_H
#define WORK_01_LINE_SETTINGS_H

#define float_mat double // TODO: figure out which type is the best here

// lighting (in settings.cpp)
extern float_mat view[3];
extern float_mat ambient[3];
extern float_mat light[][2][3];

extern float_mat ambient_reflect[3];
extern float_mat diffuse_reflect[3];
extern float_mat specular_reflect[3];

extern float_mat SPECULAR_EXPONENT;

// 3d stuff
#define ENABLE_BACKFACE_CULLING true
#define Z_BUFFER_MIN -1000

#define SPHERE_NUM_STEPS 250
#define TORUS_NUM_STEPS 250

// image stuff
#define IMAGE_HEIGHT 500
#define IMAGE_WIDTH 500
#define NUM_PIXELS (IMAGE_HEIGHT * IMAGE_WIDTH)

#define MAX_COLOR 255
#define DEFAULT_COLOR_R (char) 0
#define DEFAULT_COLOR_G (char) 0
#define DEFAULT_COLOR_B (char) 0

// color structure
struct color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

#endif //WORK_01_LINE_SETTINGS_H

