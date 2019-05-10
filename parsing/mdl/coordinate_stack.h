//
// Created by Ivan Galakhov on 2019-04-03.
//

#ifndef WORK_01_LINE_COORDINATE_STACK_H
#define WORK_01_LINE_COORDINATE_STACK_H

#include <vector>

#include "../../matrix/transformation_matrix.h"

// coordinate stack because it makes our lives easier

class CoordinateStack {
public:
    CoordinateStack();

    void push(); // push a copy (!!!!!) of the top transformation matrix to the stack
    TransformationMatrix * peek(); // peek
    void pop(); // pop the top matrix (throws an error, I guess)
    void apply_transformation(TransformationMatrix *); // apply a transformation to the top matrix

    void print_stack();

private:
    std::vector<TransformationMatrix *> stack; // here be the stack the first element of the stack (index 0) is the top of the stack


};


#endif //WORK_01_LINE_COORDINATE_STACK_H
