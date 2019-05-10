//
// Created by Ivan Galakhov on 2019-03-21.
//

#ifndef WORK_01_LINE_UNIT_MATRIX_H
#define WORK_01_LINE_UNIT_MATRIX_H

#include <iostream>
#include <cassert>
#include <list>

#include "../settings.h"

class TransformationMatrix;

class UnitMatrix {
public:
    explicit UnitMatrix(int); // constructor, takes in the size of the unit
    ~UnitMatrix(); // destructor

    void print();
    void clear();
    int size();
    float_mat * start();
    void apply_transformation(TransformationMatrix *);

    void add_unit(const std::list<float_mat> &);

private:

    void multiply_recursive(float_mat *, int, int, float_mat *, int);

    float_mat * vals;
    int num_units;
    int unit_size;
};


#endif //WORK_01_LINE_UNIT_MATRIX_H
