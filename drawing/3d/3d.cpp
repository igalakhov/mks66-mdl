//
// Created by Ivan Galakhov on 2019-03-15.
//

#include "3d.h"

void add_box(TriangleMatrix *m, float x, float y, float z, float w, float h, float d) {
    float x0 = x;
    float y0 = y;
    float z0 = z;
    float x1 = x + w;
    float y1 = y - h;
    float z1 = z - d;

    // front
    m->add_triangle(x0, y0, z0, x0, y1, z0, x1, y1, z0);
    m->add_triangle(x0, y0, z0, x1, y1, z0, x1, y0, z0);

    // back
    m->add_triangle(x0, y0, z1, x1, y0, z1, x0, y1, z1);
    m->add_triangle(x1, y1, z1, x0, y1, z1, x1, y0, z1);

    // top
    m->add_triangle(x0, y0, z0, x1, y0, z0, x1, y0, z1);
    m->add_triangle(x1, y0, z1, x0, y0, z1, x0, y0, z0);

    // bottom
    m->add_triangle(x1, y1, z0, x0, y1, z0, x0, y1, z1);
    m->add_triangle(x1, y1, z1, x1, y1, z0, x0, y1, z1);

    // left
    m->add_triangle(x0, y1, z0, x0, y0, z0, x0, y0, z1);
    m->add_triangle(x0, y0, z1, x0, y1, z1, x0, y1, z0);

    // right
    m->add_triangle(x1, y0, z0, x1, y1, z1, x1, y0, z1);
    m->add_triangle(x1, y0, z0, x1, y1, z0, x1, y1, z1);
}

void add_torus(TriangleMatrix *m, float tx, float ty, float tz, float r, float R) {
    auto torus_points = generate_torus_points(tx, ty, tz, r, R);

    int p1, p2, p3, p4;

    float_mat *s = torus_points->start();

    for (int lat = 0; lat < TORUS_NUM_STEPS; lat++) {
        for (int lon = 0; lon < TORUS_NUM_STEPS; lon++) {
            p1 = lat * TORUS_NUM_STEPS + lon;
            if (lon == TORUS_NUM_STEPS - 1) // fixes endpoints
                p2 = p1 - lon;
            else
                p2 = p1 + 1;
            p3 = (p2 + TORUS_NUM_STEPS) %
                 (TORUS_NUM_STEPS * TORUS_NUM_STEPS); // write it this way for optimized compiling
            p4 = (p1 + TORUS_NUM_STEPS) % (TORUS_NUM_STEPS * TORUS_NUM_STEPS);

            // scale index
            p1 *= 4;
            p2 *= 4;
            p3 *= 4;
            p4 *= 4;

            m->add_triangle(s[p1 + 0], s[p1 + 1], s[p1 + 2],
                            s[p3 + 0], s[p3 + 1], s[p3 + 2],
                            s[p2 + 0], s[p2 + 1], s[p2 + 2]);

            m->add_triangle(s[p1 + 0], s[p1 + 1], s[p1 + 2],
                            s[p4 + 0], s[p4 + 1], s[p4 + 2],
                            s[p3 + 0], s[p3 + 1], s[p3 + 2]);

        }
    }

    delete torus_points;
}

PointMatrix *generate_torus_points(float tx, float ty, float tz, float r, float R) {
    auto ret = new PointMatrix();

    float_mat cur_r, cur_c;
    float_mat x, y, z;

    for (int rot = 0; rot < TORUS_NUM_STEPS; rot++) {
        cur_r = (float_mat) rot / TORUS_NUM_STEPS;
        for (int circ = 0; circ < TORUS_NUM_STEPS; circ++) {
            cur_c = (float_mat) circ / TORUS_NUM_STEPS;

            x = cos(2 * M_PI * cur_r) * (r * cos(2 * M_PI * cur_c) + R) + tx;
            y = r * sin(2 * M_PI * cur_c) + ty;
            z = -1 * sin(2 * M_PI * cur_r) * (r * cos(2 * M_PI * cur_c) + R) + tz;

            ret->add_point(x, y, z);
        }
    }

    return ret;
}

void add_sphere(TriangleMatrix *m, float cx, float cy, float cz, float r) {
    auto sphere_points = generate_sphere_points(cx, cy, cz, r);

    auto s = sphere_points->start();

    int p1, p2, p3, p4;

    for (int lat = 0; lat < SPHERE_NUM_STEPS; lat++) {
        for (int lon = 0; lon < SPHERE_NUM_STEPS; lon++) {
            p1 = lat * (SPHERE_NUM_STEPS + 1) + lon;
            p2 = p1 + 1;
            p3 = (p2 + SPHERE_NUM_STEPS + 1) % (SPHERE_NUM_STEPS * (SPHERE_NUM_STEPS + 1));
            p4 = (p1 + SPHERE_NUM_STEPS + 1) % (SPHERE_NUM_STEPS * (SPHERE_NUM_STEPS + 1));

            // scale index
            p1 *= 4;
            p2 *= 4;
            p3 *= 4;
            p4 *= 4;

//            m->add_triangle(s[p1], s[p1 + 1], s[p1 + 2],s[p1], s[p1 + 1], s[p1 + 2],s[p1], s[p1 + 1], s[p1 + 2]);

            if (lon != SPHERE_NUM_STEPS - 1)
                m->add_triangle(
                        s[p1], s[p1 + 1], s[p1 + 2],
                        s[p2], s[p2 + 1], s[p2 + 2],
                        s[p3], s[p3 + 1], s[p3 + 2]);


            if (lon != 0)
                m->add_triangle(
                        s[p1], s[p1 + 1], s[p1 + 2],
                        s[p3], s[p3 + 1], s[p3 + 2],
                        s[p4], s[p4 + 1], s[p4 + 2]);
        }
    }


//    int i;
//    int num_points = sphere_points->size();
//    for(int lat = 0; lat <= SPHERE_NUM_STEPS; lat++){
//        for(int lon = 0; lon < SPHERE_NUM_STEPS; lon++){
//            i = lat * (SPHERE_NUM_STEPS + 1) + lon + 1;
//
//            p1 = (i % num_points)*4;
//            p2 = ((i+1) % num_points)*4;
//            p3 = ((SPHERE_NUM_STEPS + i + 1) % num_points)*4;
//            p4 = ((SPHERE_NUM_STEPS + i + 2) % num_points)*4;
//
//            m->add_triangle(
//                    s[p1], s[p1 + 1], s[p1 + 2],
//                    s[p2], s[p2 + 1], s[p2 + 2],
//                    s[p3], s[p3 + 1], s[p3 + 2]);
//
//            m->add_triangle(
//                    s[p2], s[p2 + 1], s[p2 + 2],
//                    s[p4], s[p4 + 1], s[p4 + 2],
//                    s[p3], s[p3 + 1], s[p3 + 2]);
//
//        }
//    }

    delete sphere_points;
}

PointMatrix *generate_sphere_points(float cx, float cy, float cz, float r) {
    auto ret = new PointMatrix();
    float_mat rot, circ;
    float_mat x, y, z;

    for (int rotation = 0; rotation < SPHERE_NUM_STEPS; rotation++) {
        rot = (float_mat) rotation / SPHERE_NUM_STEPS;
        for (int circle = 0; circle <= SPHERE_NUM_STEPS; circle++) {
            circ = (float_mat) circle / SPHERE_NUM_STEPS;

            x = r * cos(M_PI * circ) + cx;
            y = r * sin(M_PI * circ) * cos(2 * M_PI * rot) + cy;
            z = r * sin(M_PI * circ) * sin(2 * M_PI * rot) + cz;

            ret->add_point(x, y, z);
        }
    }

    return ret;

//    auto ret = new PointMatrix();
//
//    float_mat cur_r, cur_c;
//    float_mat x, y, z;
//
//    for(int rot = 0; rot < SPHERE_NUM_STEPS; rot++){
//        cur_r = ((float_mat) rot) / SPHERE_NUM_STEPS;
//        for(int circ = 0; circ <= SPHERE_NUM_STEPS; circ++){
//            cur_c = ((float_mat) circ) / SPHERE_NUM_STEPS;
//
//            x = r * cos(M_PI * cur_c) + cx;
//            y = r * sin(M_PI * cur_r) * cos(2*M_PI * cur_r) + cy;
//            z = r * sin(M_PI * cur_c) * sin(2*M_PI * cur_r) + cz;
//
//            ret->add_point(x, y, z);
//        }
//    }
//
//    ret->print();
//
//    return ret;
}

void add_box(EdgeMatrix *m, float x, float y, float z, float w, float h, float d) {
    m->add_edge(x, y, z, x + w, y, z);
    m->add_edge(x + w, y, z, x + w, y + h, z);
    m->add_edge(x + w, y + h, z, x, y + h, z);
    m->add_edge(x, y + h, z, x, y, z);

    m->add_edge(x, y, z + d, x + w, y, z + d);
    m->add_edge(x + w, y, z + d, x + w, y + h, z + d);
    m->add_edge(x + w, y + h, z + d, x, y + h, z + d);
    m->add_edge(x, y + h, z + d, x, y, z + d);

    m->add_edge(x, y, z, x, y, z + d);
    m->add_edge(x + w, y, z, x + w, y, z + d);
    m->add_edge(x, y + h, z, x, y + h, z + d);
    m->add_edge(x + w, y + h, z, x + w, y + h, z + d);
}

void add_sphere(EdgeMatrix *m, float cx, float cy, float cz, float r) {


}

void add_torus(EdgeMatrix *m, float tx, float ty, float tz, float r, float R) {
    float px, py, pz, x, y, z;

    const int steps = 50;

    float theta, phi = 0;

    for (int i = 0; i <= steps; i++) {

        theta = 0;

        px = cos(phi) * (R + r * cos(theta)) + tx;
        py = r * sin(theta) + ty;
        pz = -sin(phi) * (r * cos(theta) + R) + tz;

        for (int j = 0; j <= steps; j++) {
            x = cos(phi) * (R + r * cos(theta)) + tx;
            y = r * sin(theta) + ty;
            z = -sin(phi) * (r * cos(theta) + R) + tz;

            m->add_edge(px, py, pz, x, y, z);

            px = x;
            py = y;
            pz = z;

            theta += 2 * M_PI / steps;
        }

        phi += 2 * M_PI / steps;
    }
}