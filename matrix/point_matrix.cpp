//
// Created by Ivan Galakhov on 2019-03-23.
//

#include "point_matrix.h"

PointMatrix::PointMatrix() : UnitMatrix(1) {}

void PointMatrix::add_point(float_mat x0, float_mat y0, float_mat z0) {
    add_unit({x0, y0, z0});
}