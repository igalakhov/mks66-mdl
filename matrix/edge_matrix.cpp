//
// Created by Ivan Galakhov on 2019-02-19.
//

#include "edge_matrix.h"

EdgeMatrix::EdgeMatrix() : UnitMatrix(2) {}

void EdgeMatrix::add_edge(float_mat x1, float_mat y1, float_mat z1, float_mat x2, float_mat y2, float_mat z2) {
    add_unit({x1, y1, z1, x2, y2, z2});
}