//
// Created by Ivan Galakhov on 2019-04-29.
//

#include "lighting.h"

color *total_lighting(float_mat *normal, std::vector<double **> &sources, struct floating_color * ambient_color, struct constants * cons){
    float r = 0;
    float g = 0;
    float b = 0;
    floating_color * cur_color;
//    for(int i = 0; i < 3; i++){
//        //cur = single_lighting(normal, light[i]);
////        r += cur->r;
////        g += cur->g;
////        b += cur->b;
//    }
    for(double ** cur_source : sources){
        cur_color = single_lighting(normal, cur_source, cons);
        r += cur_color->r;
        g += cur_color->g;
        b += cur_color->b;
    }
    // add ambient only once
    floating_color *ambient = calculate_ambient(ambient_color, cons);
    r += ambient->r;
    g += ambient->g;
    b += ambient->b;

    auto ret = (color *) malloc(sizeof(color));
    ret->r = (unsigned char) constrain(r, 0, 255);
    ret->g = (unsigned char) constrain(g, 0, 255);
    ret->b = (unsigned char) constrain(b, 0, 255);

    //printf("%d, %d, %d\n", ret->r, ret->g, ret->b);

    return ret;
}
//
floating_color *single_lighting(float_mat *normal, double ** source, struct constants * cons) {
//    printf("light position: (%f, %f, %f)\n", single_light[0][0], single_light[0][1], single_light[0][2]);
//    printf("light: (%f, %f, %f)\n", single_light[1][0], single_light[1][1], single_light[1][2]);
//    printf("normal: (%f, %f, %f)\n", single_light[1][0], single_light[1][1], single_light[1][2]);

    auto ret = (floating_color *) std::malloc(sizeof(floating_color)); // color we're returning


    //floating_color *ambient = calculate_ambient();
    floating_color *diffuse = calculate_diffuse(normal, source, cons);
    floating_color *specular = calculate_specular(normal, source, cons); // calculate this last, as it modifies the normal

    //printf("ambient: %f, %f, %f\n", ambient->r, ambient->g, ambient->b);
//    printf("diffuse: %f, %f, %f\n", diffuse->r, diffuse->g, diffuse->b);
//    printf("specular: %f, %f, %f\n", specular->r, specular->g, specular->b);



    // set colors
    ret->r =  specular->r + diffuse->r;
    ret->g =  specular->g + diffuse->g;
    ret->b =  specular->b + diffuse->b;

//    ret->r = (unsigned char) constrain(std::round(ambient->r), 0, 255);
//    ret->g = (unsigned char) constrain(std::round(ambient->g), 0, 255);
//    ret->b = (unsigned char) constrain(std::round(ambient->b), 0, 255);

//    ret->r = (unsigned char) constrain(std::round(ambient->r), 0, 255);
//    ret->g = (unsigned char) constrain(std::round(ambient->g), 0, 255);
//    ret->b = (unsigned char) constrain(std::round(ambient->b), 0, 255);

    // delete stuff we don't need
    //delete ambient;
    delete diffuse;
    delete specular;

    return ret;
}
//
floating_color *calculate_diffuse(float_mat *normal, double ** light, struct constants * cons) {
    auto ret = (floating_color *) std::malloc(sizeof(floating_color));

    ret->r = light[1][0];
    ret->g = light[1][1];
    ret->b = light[1][2];

    float_mat dot = dot_product(normal, light[0]);
    if(dot < 0)
        dot = 0;
    //printf("%f\n", dot);
    multiply_constant(ret, dot);
    multiply_through(ret, diffuse_reflect);
    ret->r *= cons->r[DIFFUSE_R];
    ret->g *= cons->g[DIFFUSE_R];
    ret->b *= cons->b[DIFFUSE_R];
    //fix_color(ret);

    //printf("%f, %f, %f\n", ret->r, ret->g, ret->b);

    return ret;
}
//
floating_color *calculate_specular(float_mat *normal, double ** light, struct constants * cons) {
    auto ret = (floating_color *) std::malloc(sizeof(floating_color));

    // copy the normal
    auto normal_copy = (float_mat * ) std::malloc(sizeof(float_mat) * 3);
    normal_copy[0] = normal[0];
    normal_copy[1] = normal[1];
    normal_copy[2] = normal[2];

    ret->r = light[1][0];
    ret->g = light[1][1];
    ret->b = light[1][2];

    // copy light
    auto light_pos = (double *) std::malloc(sizeof(double) * 3);
    light_pos[0] = light[0][0];
    light_pos[1] = light[0][1];
    light_pos[2] = light[0][2];
    normalize_in_place(light_pos);

    float_mat first_dot = dot_product(normal, light_pos);

    if (first_dot < 0) {
        ret->r = ret->g = ret->b = 0;
        return ret;
    }

    scalar_mult(normal_copy, first_dot * 2);
    subtract(normal_copy, light_pos);
    float_mat second_dot = dot_product(normal_copy, view);
    if(second_dot < 0)
        second_dot = 0; // this line
    //multiply_through(ret, specular_reflect);
    ret->r *= cons->r[SPECULAR_R];
    ret->g *= cons->g[SPECULAR_R];
    ret->b *= cons->b[SPECULAR_R];
    multiply_constant(ret, std::pow(second_dot, 4.0));
    //fix_color(ret);

    std::free(normal_copy);


    return ret;
}
//
floating_color *calculate_ambient(struct floating_color * ambient_color, struct constants * cons) {
    auto ret = (floating_color *) std::malloc(sizeof(floating_color));

    ret->r = (ambient_color->r * cons->r[AMBIENT_R]);
    ret->g = (ambient_color->g * cons->g[AMBIENT_R]);
    ret->b = (ambient_color->b * cons->b[AMBIENT_R]);

    //printf("constants: %f, %f, %f", cons->r[AMBIENT_R], cons->g[AMBIENT_R], cons->b[AMBIENT_R]);

    //printf("ambient: %f, %f, %f\n", ret->r, ret->g, ret->b);

    return ret;

}
//
//// utils
void copy_color(floating_color *to, float_mat *from) {
    to->r = from[0];
    to->g = from[1];
    to->b = from[2];
}
//
void multiply_through(floating_color *c, float_mat *m) {
    c->r = c->r * m[0];
    c->g = c->g * m[0];
    c->b = c->b * m[0];
};

void fix_color(floating_color *c) {
    c->r = constrain(c->r, 0, 255);
    c->g = constrain(c->g, 0, 255);
    c->b = constrain(c->b, 0, 255);
}

void multiply_constant(floating_color *c, float_mat val) {
    c->r *= val;
    c->g *= val;
    c->b *= val;
}
//
float_mat constrain(float_mat val, float_mat lo, float_mat hi) {
    if (val < lo)
        return lo;
    if (val > hi)
        return hi;
    return val;
}