//
// Created by Ivan Galakhov on 2019-04-03.
//

#include "coordinate_stack.h"

TransformationMatrix * CoordinateStack::peek(){
    return stack.at(0);
}

void CoordinateStack::print_stack(){
    std::cout << "{" << std::endl;

    for(auto & val : stack ){
        val->print_self();
    }

    std::cout << "}" << std::endl;
}

CoordinateStack::CoordinateStack(){
    stack.insert(stack.begin(), TransformationMatrix::identity());
}

void CoordinateStack::apply_transformation(TransformationMatrix * m) {
    stack.front()->add_transformation_inverse(m);
}

void CoordinateStack::push(){
    // make a copy of the top element (0)
    auto cpy = TransformationMatrix::copy(stack.at(0));

    stack.insert(stack.begin(), cpy);
}

void CoordinateStack::pop(){
    stack.erase(stack.begin());
}