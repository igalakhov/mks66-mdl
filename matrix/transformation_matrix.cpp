//
// Created by Ivan Galakhov on 2019-02-19.
//

#include "transformation_matrix.h"

// returns the start of the matrix val array
// the array is always of size 16
float_mat * TransformationMatrix::get_start() {
    return vals;
}

void TransformationMatrix::copy_vals(TransformationMatrix * t){
    float_mat * s = t->get_start();

    for(int i = 0; i < 16; i++)
        vals[i] = s[i];
}

// prints the transformation matrix
void TransformationMatrix::print_self() {
    std::cout << "[\n";
    for(int i = 0; i < 16; i++){

        if(vals[i] < 10) {
            std::cout << vals[i] << "   ";
        } else if(vals[i] < 100){
            std::cout << vals[i] << "  ";
        } else {
            std::cout << vals[i] << " ";
        }


        if((i+1) % 4 == 0)
            std::cout << "\n";
    }
    std::cout << "]\n";
}

// constructor 2
TransformationMatrix::TransformationMatrix(float_mat * v){
    vals = (float_mat *) std::malloc(16 * sizeof(float_mat));
    for(int i = 0; i < 16; i++){
        vals[i] = v[i];
    }

    delete v;
}

// static constructor thingy
TransformationMatrix * TransformationMatrix::from_edge(EdgeMatrix * m) {
    assert(m->size() >= 4);
    float_mat * p = m->start();
    TransformationMatrix * ret = new TransformationMatrix(new float_mat[16]{
        p[0], p[4], p[8], p[12],
        p[1], p[5], p[9], p[13],
        p[2], p[6], p[10], p[14],
        p[3], p[7], p[11], p[15]
    });

    return ret;
}

// multiply self by transformation matrix
// no optimization needed here since this is basically O(1) in terms of other things happening
void TransformationMatrix::add_transformation(TransformationMatrix * m) {
    float_mat * s = m->get_start();

    auto new_vals = (float_mat *) std::malloc(16 * sizeof(float_mat));

    // epic O(n^3)
    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            new_vals[row * 4 + col] = (s[row * 4 + 0] * vals[0 + col]) +
                                    (s[row * 4 + 1] * vals[4 + col]) +
                                    (s[row * 4 + 2] * vals[8 + col]) +
                                    (s[row * 4 + 3] * vals[12 + col]);
        }
    }

    // swap
    float_mat * temp = vals;
    vals = new_vals;
    std::free(temp);
}

void TransformationMatrix::add_transformation_inverse(TransformationMatrix * m) {
    float_mat * s = m->get_start();

    auto new_vals = (float_mat *) std::malloc(16 * sizeof(float_mat));

    // epic O(n^3)
    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            new_vals[row * 4 + col] = (vals[row * 4 + 0] * s[0 + col]) +
                                      (vals[row * 4 + 1] * s[4 + col]) +
                                      (vals[row * 4 + 2] * s[8 + col]) +
                                      (vals[row * 4 + 3] * s[12 + col]);
        }
    }

    // swap
    float_mat * temp = vals;
    vals = new_vals;
    std::free(temp);
}

// special matrix static constructors

TransformationMatrix * TransformationMatrix::zero(){
    auto ret = new TransformationMatrix(new float_mat[16]{
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0
    });
    return ret;
}

TransformationMatrix * TransformationMatrix::identity(){
    auto ret = TransformationMatrix::zero();
    float_mat * s = ret->get_start();
    for(int i = 0; i < 4; i++, s += 5)
        *s = 1;
    return ret;
}

TransformationMatrix * TransformationMatrix::rotationX(float_mat x){
    x = x * (float_mat) M_PI/180;

    auto ret = new TransformationMatrix(new float_mat[16]{
            1, 0, 0, 0,
            0, cos(x), -sin(x), 0,
            0, sin(x), cos(x), 0,
            0, 0, 0, 1
    });

    return ret;
}

TransformationMatrix * TransformationMatrix::rotationY(float_mat y){
    y = y * (float_mat) M_PI/180;

    auto ret = new TransformationMatrix(new float_mat[16]{
            cos(y), 0, sin(y), 0,
            0, 1, 0, 0,
            -sin(y), 0, cos(y), 0,
            0, 0, 0, 1
    });

    return ret;
}

TransformationMatrix * TransformationMatrix::rotationZ(float_mat z){
    z = z * (float_mat) M_PI/180;

    auto ret = new TransformationMatrix(new float_mat[16]{
            cos(z), -sin(z), 0, 0,
            sin(z), cos(z), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    });

    return ret;
}

TransformationMatrix * TransformationMatrix::rotationXYZ(float_mat x, float_mat y, float_mat z){
    auto ret = TransformationMatrix::identity();
    auto rx = TransformationMatrix::rotationX(x);
    auto ry = TransformationMatrix::rotationY(y);
    auto rz = TransformationMatrix::rotationZ(z);

    ret->add_transformation(rx);
    ret->add_transformation(ry);
    ret->add_transformation(rz);

    delete rx;
    delete ry;
    delete rz;

    return ret;
}

TransformationMatrix * TransformationMatrix::translation(float_mat a, float_mat b, float_mat c){
    auto ret = new TransformationMatrix(new float_mat[16]{
            1, 0, 0, a,
            0, 1, 0, b,
            0, 0, 1, c,
            0, 0, 0, 1
    });

    return ret;
}

TransformationMatrix * TransformationMatrix::dilation(float_mat a, float_mat b, float_mat c){
    auto ret = new TransformationMatrix(new float_mat[16]{
            a, 0, 0, 0,
            0, b, 0, 0,
            0, 0, c, 0,
            0, 0, 0, 1
    });

    return ret;
}

TransformationMatrix * TransformationMatrix::copy(TransformationMatrix * m) {
    auto ret = TransformationMatrix::identity();

    ret->copy_vals(m);

    return ret;
}

// destructor
TransformationMatrix::~TransformationMatrix() {
    std::free(vals);
}