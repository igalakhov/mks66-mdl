#include <iostream>
#include <random>

#include "settings.h"

#include "drawing/drawer.h"
#include "parsing/mdl/mdl_parser.h"
#include "matrix/transformation_matrix.h"
#include "matrix/point_matrix.h"
#include "drawing/3d/3d.h"
#include "parsing/obj_parser.h"
#include "parsing/mdl/coordinate_stack.h"
#include "matrix/utils/vector_utils.h"

int main(){

    // set up relevant constants
    normalize_in_place(view);
    normalize_in_place(light[0][0]);
    normalize_in_place(light[1][0]);
    normalize_in_place(light[2][0]);

    //printf("light 1: (%f, %f, %f)\n", light[0][0][0], light[0][0][1], light[0][0][2]);
    //printf("light 2: (%f, %f, %f)\n", light[1][0][0], light[1][0][1], light[1][0][2]);
//
////
    //auto p = new MDLParser("submissionscript.mdl");
//
    //p->run_file();

    auto m = new OBJFileParser("../resources/teapot/teapot.obj");

    auto d = new Drawer();

    auto s = m->get_triangle_matrix();

    s->apply_transformation(TransformationMatrix::dilation(100, 100, 100));
    s->apply_transformation(TransformationMatrix::rotationXYZ(30, -45, -43));
    s->apply_transformation(TransformationMatrix::translation(200, 150, 0));

    d->draw_polygons(s);

    d->display();

    d->save("../teapot_with_culling.ppm", ".png");

//
//    for(int i = 1; i <= 206; i++){
//        std::string f_name = "../resources/default_dance/dance_000";
//
//
//        if(i < 10){
//            f_name += "00" + std::to_string(i);
//        } else if(i < 100){
//            f_name += "0" + std::to_string(i);
//        } else {
//            f_name += "" + std::to_string(i);
//        }
//
//        f_name += ".obj";
//
//        float r = (float) ((i-1)/206.0) * 360; // rotation
//
//        std::cout << f_name << std::endl;
//        std::cout << r << std::endl;
//
//        auto o = new OBJFileParser(f_name);
//
//        auto e = o->get_triangle_matrix();
//
//        e->apply_transformation(TransformationMatrix::dilation(110, 110, 110));
//        //e->apply_transformation(TransformationMatrix::rotationX(180));
//        e->apply_transformation(TransformationMatrix::rotationY(r));
//        e->apply_transformation(TransformationMatrix::translation(250, 25, 0));
//
//        auto d = new Drawer();
//
//        d->draw_polygons(e);
//
//        if(i < 10) {
//            d->save("../renders/default_dance/dance_00" + std::to_string(i) + ".ppm", ".ppm");
//        } else if(i < 100){
//            d->save("../renders/default_dance/dance_0" + std::to_string(i) + ".ppm", ".ppm");
//        } else {
//            d->save("../renders/default_dance/dance_" + std::to_string(i) + ".ppm", ".ppm");
//        }
//
//    }


}
