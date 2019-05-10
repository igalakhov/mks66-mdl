//
// Created by Ivan Galakhov on 2019-03-23.
//

#include "triangle_matrix.h"

TriangleMatrix::TriangleMatrix() : UnitMatrix(3) {}

void TriangleMatrix::add_triangle(float_mat x0, float_mat y0, float_mat z0,
                                  float_mat x1 , float_mat y1, float_mat z1,
                                  float_mat x2, float_mat y2, float_mat z2) {
    add_unit({x0, y0, z0, x1, y1, z1, x2, y2, z2});
}

