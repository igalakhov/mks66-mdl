//
// Created by Ivan Galakhov on 2019-03-09.
//

#include "parametric.h"

void add_bezier(EdgeMatrix * m, float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3){
    const int num_steps = 1000; // keep it even

    float step = (float) 1 / num_steps;

    float cur = 0;

    auto cur_x = (float) (pow((1-cur), 3) * x0 + 3*pow(1-cur, 2)*cur*x1 + 3*(1-cur)*cur*cur*x2 + cur*cur*cur*x3);
    auto cur_y = (float) (pow((1-cur), 3) * y0 + 3*pow(1-cur, 2)*cur*y1 + 3*(1-cur)*cur*cur*y2 + cur*cur*cur*y3);
    float px, py;

    for(int i = 0; i <= num_steps; i++){

        px = cur_x;
        py = cur_y;

        cur_x = (float) (pow((1-cur), 3) * x0 + 3*pow(1-cur, 2)*cur*x1 + 3*(1-cur)*cur*cur*x2 + cur*cur*cur*x3);
        cur_y = (float) (pow((1-cur), 3) * y0 + 3*pow(1-cur, 2)*cur*y1 + 3*(1-cur)*cur*cur*y2 + cur*cur*cur*y3);

        m->add_edge(px, py, 0, cur_x, cur_y, 0);

        cur += step;
    }
}

void add_hermite(EdgeMatrix * m, float x0, float y0, float x1, float y1, float rx0, float ry0, float rx1, float ry1){
    const int num_steps = 1000; // keep it even

    float step = (float) 1 / num_steps;

    float cur = 0;

    float cur_x = (2*cur*cur*cur - 3*cur*cur + 1) * x0 + (cur*cur*cur - 2*cur*cur + cur) * rx0 + (-2*cur*cur*cur + 3*cur*cur)*x1 + (cur*cur*cur - cur*cur)*rx1;
    float cur_y = (2*cur*cur*cur - 3*cur*cur + 1) * y0 + (cur*cur*cur - 2*cur*cur + cur) * ry0 + (-2*cur*cur*cur + 3*cur*cur)*y1 + (cur*cur*cur - cur*cur)*ry1;
    float px, py;

    for(int i = 0; i <= num_steps; i++){

        px = cur_x;
        py = cur_y;

        cur_x = (2*cur*cur*cur - 3*cur*cur + 1) * x0 + (cur*cur*cur - 2*cur*cur + cur) * rx0 + (-2*cur*cur*cur + 3*cur*cur)*x1 + (cur*cur*cur - cur*cur)*rx1;
        cur_y = (2*cur*cur*cur - 3*cur*cur + 1) * y0 + (cur*cur*cur - 2*cur*cur + cur) * ry0 + (-2*cur*cur*cur + 3*cur*cur)*y1 + (cur*cur*cur - cur*cur)*ry1;

        m->add_edge(px, py, 0, cur_x, cur_y, 0);

        cur += step;
    }
}

void add_circle(EdgeMatrix * m, float cx, float cy, float cz, float r){

    const int num_steps = 1000; // keep it even

    float step = (float) M_PI * 2 / num_steps;

    float cur = 0;

    float cur_x = cx + r * cos(cur);
    float cur_y = cy + r * sin(cur);
    float px, py;

    for(int i = 0; i <= num_steps; i++){

        px = cur_x;
        py = cur_y;

        cur_x = cx + r * cos(cur);
        cur_y = cy + r * sin(cur);

        m->add_edge(px, py, cz, cur_x, cur_y, cz);

        cur += step;
    }

}
