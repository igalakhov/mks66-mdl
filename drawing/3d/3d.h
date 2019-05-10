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

void add_box(TriangleMatrix *, float, float, float, float, float, float);
void add_sphere(TriangleMatrix *, float, float, float, float);
void add_torus(TriangleMatrix *, float, float, float, float, float);

// point generation
PointMatrix * generate_sphere_points(float, float, float, float);
PointMatrix * generate_torus_points(float, float, float, float, float);

#endif //WORK_01_LINE_3D_H
