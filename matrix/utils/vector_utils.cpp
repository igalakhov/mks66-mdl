//
// Created by Ivan Galakhov on 2019-03-23.
//

#include "vector_utils.h"

// all of these assume vectors of size 3

float_mat * normalize(float_mat * vec){
    auto ret = new float_mat[3];
    double len = sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);

    ret[0] = (float)(vec[0] / len);
    ret[1] = (float)(vec[1] / len);
    ret[2] = (float)(vec[2] / len);

    return ret;

}

void normalize_in_place(float_mat * vec){
    double len = sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);

    vec[0] = (float)(vec[0] / len);
    vec[1] = (float)(vec[1] / len);
    vec[2] = (float)(vec[2] / len);
}

float dot_product(float_mat * vec1, float_mat * vec2){
    return vec1[0]*vec2[0] + vec1[1]*vec2[1] + vec1[2]*vec2[2];
}

float_mat * cross_product(float_mat * vec1, float_mat * vec2){
    auto normal = new float_mat[3];

    normal[0] = vec1[1]*vec2[2] - vec1[2]*vec2[1];
    normal[1] = vec1[2]*vec2[0] - vec1[0]*vec2[2];
    normal[2] = vec1[0]*vec2[1] - vec1[1]*vec2[0];

    return normal;
}

void scalar_mult(float_mat * v, float_mat c){
    v[0] *= c;
    v[1] *= c;
    v[2] *= c;
}

void subtract(float_mat * v1, float_mat * v2){
    v1[0] -= v2[0];
    v1[1] -= v2[1];
    v1[2] -= v2[2];
}

void add(float_mat * v1, float_mat * v2){
    v1[0] += v2[0];
    v1[1] += v2[1];
    v1[2] += v2[2];
}