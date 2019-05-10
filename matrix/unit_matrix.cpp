//
// Created by Ivan Galakhov on 2019-03-21.
//

#include "unit_matrix.h"
#include "transformation_matrix.h"

// general unit matrix

void UnitMatrix::clear() {
    free(vals);
    num_units = 0;
    this->vals = (float_mat * ) std::malloc(0);
}

// add a new unit
void UnitMatrix::add_unit(const std::list<float_mat> & args) {

    assert(args.size() == unit_size * 3);

    vals = (float_mat *) std::realloc(vals, (size_t) sizeof(float_mat) * (4*num_units*unit_size + (args.size()/3)*4));

    float_mat * s = vals + num_units*unit_size*4;

    auto l_front = args.begin();



    for(int i = 0; i < args.size()/3; i++){
        *s = *l_front;
        s++; std::advance(l_front, 1);
        *s = *l_front;
        s++; std::advance(l_front, 1);
        *s = *l_front;
        s++; std::advance(l_front, 1);
        *s = 1;
        s++;
    }

    num_units += 1;
}


// apply some kind of transformation
void UnitMatrix::apply_transformation(TransformationMatrix * m){
    auto new_matrix = (float_mat *) std::malloc(sizeof(float_mat) * 4 * num_units * unit_size);

    multiply_recursive(m->get_start(), 0, num_units * unit_size, new_matrix, 0); // will spawn a max of 16 threads

    std::free(vals);

    vals = new_matrix;
}

// multiply
void UnitMatrix::multiply_recursive(float_mat * m, int start, int end, float_mat * new_matrix, int depth) {

    if(!depth) { // if the depth is 0
        for (int i = start; i < end; i++) {
            for (int j = 0; j < 4; j++) {
                new_matrix[i * 4 + j] =
                        vals[i * 4 + 0] * m[j * 4 + 0] +
                        vals[i * 4 + 1] * m[j * 4 + 1] +
                        vals[i * 4 + 2] * m[j * 4 + 2] +
                        vals[i * 4 + 3] * m[j * 4 + 3];

            }
        }

        return;
    }
}

// get start
float_mat * UnitMatrix::start(){
    return vals;
}

// size
int UnitMatrix::size(){
    return num_units;
}

// print
void UnitMatrix::print(){
    std::cout << "[\n";
    for(int j = 0; j < 4; j++){
        float_mat * s = vals + j;
        for(int i = 0; i < num_units*unit_size; i++){
            float_mat val = s[4*i];
            if(val < 10){
                std::cout << " " << val << "    ";
            } else if(val < 100){
                std::cout << val << "    ";
            } else if(val < 1000){
                std::cout << val << "   ";
            } else if(val < 10000){
                std::cout << val << "  ";
            } else if(val < 100000){
                std::cout << val << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "]\n";
}

// constructor
UnitMatrix::UnitMatrix(int unit_size){
    this->num_units = 0;
    this->unit_size = unit_size;
    this->vals = (float_mat * ) std::malloc(0);
}

// destructor
UnitMatrix::~UnitMatrix(){
    std::free(vals); // bye
}