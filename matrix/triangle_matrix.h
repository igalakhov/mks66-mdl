//
// Created by Ivan Galakhov on 2019-03-23.
//

#ifndef WORK_01_LINE_TRIANGLE_MATRIX_H
#define WORK_01_LINE_TRIANGLE_MATRIX_H

#include <iostream>
#include <thread>
#include "math.h"

#include "unit_matrix.h"
#include "../settings.h"


class TriangleMatrix: public UnitMatrix {

public:
    TriangleMatrix();

    void add_triangle(float_mat, float_mat, float_mat, float_mat, float_mat, float_mat, float_mat, float_mat, float_mat);
};

#endif //WORK_01_LINE_TRIANGLE_MATRIX_H
