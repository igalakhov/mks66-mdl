//
// Created by Ivan Galakhov on 2019-02-06.
//
#include "display.h"
#include "../matrix/edge_matrix.h"

#ifndef WORK_01_LINE_DRAWER_H
#define WORK_01_LINE_DRAWER_H

#include <cassert>
#include "display.h"
#include <cmath>
#include "../matrix/point_matrix.h"
#include "../matrix/edge_matrix.h"
#include "../matrix/triangle_matrix.h"
#include "../matrix/utils/vector_utils.h"
#include "lighting/lighting.h"

class Drawer : public Display {
public:
    Drawer(); // constructor
    ~Drawer(); // destructor

    // drawing basics
    void draw_points(PointMatrix *);
    void draw_edges(EdgeMatrix * );
    void draw_polygons(TriangleMatrix *);

    void draw_line(int, int, float_mat, int, int, float_mat);
    void draw_line_new(int, int, float_mat, int, int, float_mat);
    void draw_line_simon(double, double, double, double, double, double);
    void draw_line_steep(int, int, float_mat, int, int, float_mat, int, int, int);
    void draw_line_shallow(int, int, float_mat, int, int, float_mat, int, int, int);
    void scan_line(float_mat *, float_mat *, float_mat *);
    void change_color(unsigned char, unsigned char, unsigned char);
    void set(int, int, float_mat); // set a specific point to the current color

protected:

private:
    struct color cur_color; // current drawing color

    float_mat * z_buffer;
};


#endif //WORK_01_LINE_DRAWER_H
