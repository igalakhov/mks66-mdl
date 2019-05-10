# include "settings.h"

char axis[3][8] = {"X", "Y", "Z"};

float_mat view[3] = {0, 0, 1};
float_mat ambient[3] = {100, 100, 100};
float_mat light[3][2][3] = {{{-0.5f, 0.5f, 1.0f}, {255, 0, 0}}, {{0.5f, -0.5f, 1.0f}, {0, 255, 0}}
        ,{{-0.5, -0.5f, 1.0f}, {0, 0, 255}}};

float_mat ambient_reflect[3] = {0.1f, 0.1f, 0.1f};
//float_mat ambient_reflect[3] = {0.0f, 0.0f, 0.0f};
float_mat diffuse_reflect[3] = {0.5f, 0.0f, 0.5f};
//float_mat diffuse_reflect[3] = {0.0f, 0.0f, 0.0f};
float_mat specular_reflect[3] = {0.5f, 0.5f, 0.5f};
//float_mat specular_reflect[3] = {0.0f, 0.0f, 0.0f};

float_mat SPECULAR_EXPONENT = 5.0f;

# include "settings.h"

//char axis[3][8] = {"X", "Y", "Z"};
//
//float_mat view[3] = {0, 0, 1};
//float_mat ambient[3] = {100, 100, 100};
//float_mat light[2][2][3] = {{{0.5f, 0.5f, 1.0f}, {255, 100, 0}}, {{-2.0f, -0.5f, 2.0f}, {100, 0, 0}}};
//
//float_mat ambient_reflect[3] = {0.1f, 0.1f, 0.1f};
////float_mat ambient_reflect[3] = {0.0f, 0.0f, 0.0f};
//float_mat diffuse_reflect[3] = {0.5f, 0.0f, 0.5f};
////float_mat diffuse_reflect[3] = {0.0f, 0.0f, 0.0f};
//float_mat specular_reflect[3] = {0.01f, 0.1f, 0.1f};
////float_mat specular_reflect[3] = {0.0f, 0.0f, 0.0f};
//
//float_mat SPECULAR_EXPONENT = 4;

