//
// Created by Ivan Galakhov on 2019-03-23.
//

#ifndef WORK_01_LINE_VECTOR_UTILS_H
#define WORK_01_LINE_VECTOR_UTILS_H

#include "../../settings.h"
#include "math.h"

float_mat * cross_product(float_mat *, float_mat *);
float dot_product(float_mat *, float_mat *);
float_mat * normalize(float_mat *);
void normalize_in_place(float_mat *);
void scalar_mult(float_mat *, float_mat);
void subtract(float_mat *, float_mat *);
void add(float_mat *, float_mat *);

#endif //WORK_01_LINE_VECTOR_UTILS_H
