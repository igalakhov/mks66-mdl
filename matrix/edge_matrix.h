//
// Created by Ivan Galakhov on 2019-02-19.
//


#ifndef WORK_01_LINE_EDGE_MATRIX_H
#define WORK_01_LINE_EDGE_MATRIX_H

#include <iostream>
#include <thread>
#include "math.h"

#include "unit_matrix.h"
#include "../settings.h"


class EdgeMatrix: public UnitMatrix {

public:
    EdgeMatrix();

    void add_edge(float_mat, float_mat, float_mat, float_mat, float_mat, float_mat);
};


#endif //WORK_01_LINE_EDGE_MATRIX_H
