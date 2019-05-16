#ifndef WORK_01_LINE_LIGHTING_H
#define WORK_01_LINE_LIGHTING_H

#include <iostream>
#include <cmath>
#include <vector>
#include "../../settings.h"
#include "../../matrix/utils/vector_utils.h"
#include "../../compiler/parser.h"

struct floating_color { // floating point color for in between calculations. only used here
    float_mat r;
    float_mat g;
    float_mat b;
};

color * total_lighting(float_mat *, std::vector<double **> &, struct floating_color *, struct constants *);

floating_color * single_lighting(float_mat *, double **, struct constants *);

floating_color * calculate_ambient(struct floating_color *, struct constants *);
floating_color * calculate_diffuse(float_mat *, double **, struct constants *);
floating_color * calculate_specular(float_mat *, double **, struct constants *);

void multiply_through(floating_color *, float_mat *);
void copy_color(floating_color *, float_mat *);

void fix_color(color *);
void fix_color(floating_color *);
float_mat constrain(float_mat, float_mat, float_mat);
void multiply_constant(floating_color *, float_mat);


#endif //WORK_01_LINE_LIGHTING_H


