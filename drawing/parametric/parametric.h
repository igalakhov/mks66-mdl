//
// Created by Ivan Galakhov on 2019-03-09.
//

#ifndef WORK_01_LINE_PARAMETRIC_H
#define WORK_01_LINE_PARAMETRIC_H

#include <iostream>
#include <tuple>

#include "../../matrix/edge_matrix.h"

void add_circle(EdgeMatrix *, float, float, float, float);
void add_bezier(EdgeMatrix *, float, float, float, float, float, float, float, float);
void add_hermite(EdgeMatrix *, float, float, float, float, float, float, float, float);

#endif //WORK_01_LINE_PARAMETRIC_H
