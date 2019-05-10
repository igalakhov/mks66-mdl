//
// Created by Ivan Galakhov on 2019-02-19.
//

#ifndef WORK_01_LINE_TRANSFORMATION_MATRIX_H
#define WORK_01_LINE_TRANSFORMATION_MATRIX_H

#include <cassert>

#include "edge_matrix.h"

#include "../settings.h"

class EdgeMatrix;

class TransformationMatrix {
public:
    TransformationMatrix(float_mat *); // constructor
    ~TransformationMatrix(); // destructor

    void print_self(); // print self

    float_mat * get_start();

    // transformations
    void add_transformation(TransformationMatrix *); // add a transformation
    void add_transformation_inverse(TransformationMatrix *);

    // copying
    void copy_vals(TransformationMatrix *);

    // for conversion (basically never used but it's here I guess)
    static TransformationMatrix * from_edge(EdgeMatrix *);

    // static constructors for making special transformation matrixes and copies
    static TransformationMatrix * copy(TransformationMatrix *);
    static TransformationMatrix * identity();
    static TransformationMatrix * zero();
    static TransformationMatrix * rotationX(float_mat);
    static TransformationMatrix * rotationY(float_mat);
    static TransformationMatrix * rotationZ(float_mat);
    static TransformationMatrix * rotationXYZ(float_mat, float_mat, float_mat);
    static TransformationMatrix * translation(float_mat, float_mat, float_mat);
    static TransformationMatrix * dilation(float_mat, float_mat, float_mat);


private:
    float_mat * vals; // ROW MAJOR!!!
};


#endif //WORK_01_LINE_TRANSFORMATION_MATRIX_H
