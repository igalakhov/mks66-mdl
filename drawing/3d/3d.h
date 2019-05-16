//
// Created by Ivan Galakhov on 2019-03-15.
//

#ifndef WORK_01_LINE_3D_H
#define WORK_01_LINE_3D_H

#include "../../matrix/point_matrix.h"
#include "../../matrix/edge_matrix.h"
#include "../../matrix/triangle_matrix.h"

void add_box(EdgeMatrix *, float, float, float, float, float, float);
void add_sphere(EdgeMatrix *, float, float, float, float);
void add_torus(EdgeMatrix *, float, float, float, float, float);

void add_box(TriangleMatrix *, double, double, double, double, double, double);
void add_sphere(TriangleMatrix *, double, double, double, double);
void add_torus(TriangleMatrix *, double, double, double, double, double);

// point generation
PointMatrix * generate_sphere_points(double, double, double, double);
PointMatrix * generate_torus_points(double, double, double, double, double);

#endif //WORK_01_LINE_3D_H
