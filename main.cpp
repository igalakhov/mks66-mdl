#include <iostream>
#include <random>

#include "settings.h"
#include "compiler/parser.h"
#include "matrix/triangle_matrix.h"
#include "matrix/edge_matrix.h"
#include "drawing/drawer.h"
#include "build/mdl.tab.hh"
#include "compiler/symbol_table.h"
#include "parsing/mdl/coordinate_stack.h"
#include "drawing/3d/3d.h"
#include "parsing/obj_parser.h"

void my_main() {
    // set up
    auto cord_stack = new CoordinateStack();

    auto edge_matrix = new EdgeMatrix();
    auto triangle_matrix = new TriangleMatrix();
    auto drawer = new Drawer();

    // default light
    auto default_light = (double **) std::malloc(sizeof(double **) * 2);
    default_light[0] = (double *) std::malloc(sizeof(double *) * 3);
    default_light[1] = (double *) std::malloc(sizeof(double *) * 3);
    default_light[0][0] = 0.5;
    default_light[0][1] = 0.75;
    default_light[0][2] = 1;
    //normalize_in_place(default_light[0]);

    default_light[1][0] = 255;
    default_light[1][1] = 255;
    default_light[1][2] = 255;

    // default reflect
    struct constants white;
    white.r[AMBIENT_R] = 0.1;
    white.g[AMBIENT_R] = 0.1;
    white.b[AMBIENT_R] = 0.1;

    white.r[DIFFUSE_R] = 0.5;
    white.g[DIFFUSE_R] = 0.5;
    white.b[DIFFUSE_R] = 0.5;

    white.r[SPECULAR_R] = 0.5;
    white.g[SPECULAR_R] = 0.5;
    white.b[SPECULAR_R] = 0.5;

    struct constants *default_constants;
    default_constants = &white;

    // values
    struct floating_color ambient = {50, 50, 50};

    bool custom_light = false;
    std::vector<double **> light_sources; // array of light sources
    light_sources.push_back(default_light);


    // actually run the commands
    for (int i = 0; i < lastop; i++) {

        //std::cout << "yes" << std::endl;

        //printf("%d: \n", i);
        struct command cur = op[i];
        switch (cur.opcode) {

            case TORUS: {
                add_torus(triangle_matrix,
                          cur.op.torus.d[0],
                          cur.op.torus.d[1],
                          cur.op.torus.d[2],
                          cur.op.torus.r0,
                          cur.op.torus.r1
                );
                triangle_matrix->apply_transformation(cord_stack->peek());
                if (cur.op.torus.constants != nullptr)
                    drawer->draw_polygons(triangle_matrix, light_sources, &ambient, cur.op.torus.constants->s.c);
                else
                    drawer->draw_polygons(triangle_matrix, light_sources, &ambient, default_constants);
                triangle_matrix->clear();
                break;
            }

                // shapes and displaying
            case BOX: {
                add_box(triangle_matrix,
                        cur.op.box.d0[0],
                        cur.op.box.d0[1],
                        cur.op.box.d0[2],
                        cur.op.box.d1[0],
                        cur.op.box.d1[1],
                        cur.op.box.d1[2]
                );
                triangle_matrix->apply_transformation(cord_stack->peek());
                if (cur.op.box.constants != nullptr)
                    drawer->draw_polygons(triangle_matrix, light_sources, &ambient, cur.op.box.constants->s.c);
                else
                    drawer->draw_polygons(triangle_matrix, light_sources, &ambient, default_constants);
                triangle_matrix->clear();
                break;
            }
            case SPHERE: {
                add_sphere(triangle_matrix,
                           cur.op.sphere.d[0],
                           cur.op.sphere.d[1],
                           cur.op.sphere.d[2],
                           cur.op.sphere.r);
                if (cur.op.sphere.cs != nullptr) {
                    //s->lookup_symbol(cur.op.sphere.cs->name)->s.m->print_self();
                    triangle_matrix->apply_transformation(s->lookup_symbol(cur.op.sphere.cs->name)->s.m);
                }else
                    triangle_matrix->apply_transformation(cord_stack->peek());
                if (cur.op.sphere.constants != nullptr)
                    drawer->draw_polygons(triangle_matrix, light_sources, &ambient, cur.op.sphere.constants->s.c);
                else
                    drawer->draw_polygons(triangle_matrix, light_sources, &ambient, default_constants);
                triangle_matrix->clear();
                break;
            }
            case LINE: {
                auto temp = new EdgeMatrix();

                temp->add_edge(cur.op.line.p0[0],
                               cur.op.line.p0[1],
                               cur.op.line.p0[2],
                               cur.op.line.p1[0],
                               cur.op.line.p1[1],
                               cur.op.line.p1[2]
                        );

                temp->apply_transformation(cord_stack->peek());

                drawer->draw_edges(edge_matrix);

                break;
            }


                // stacks and transformations
            case MOVE: {
                cord_stack->apply_transformation(TransformationMatrix::translation(
                        cur.op.move.d[0],
                        cur.op.move.d[1],
                        cur.op.move.d[2]
                ));
                break;
            }

            case ROTATE: {
                switch ((int) std::round(cur.op.rotate.axis)) {
                    case 0:
                        cord_stack->apply_transformation(TransformationMatrix::rotationX(cur.op.rotate.degrees));
                        break;
                    case 1:
                        cord_stack->apply_transformation(TransformationMatrix::rotationY(cur.op.rotate.degrees));
                        break;
                    case 2:
                        cord_stack->apply_transformation(TransformationMatrix::rotationZ(cur.op.rotate.degrees));
                        break;
                    default:
                        break;
                }
                break;
            }

            case SCALE: {
                cord_stack->apply_transformation(TransformationMatrix::dilation(
                        cur.op.scale.d[0],
                        cur.op.scale.d[1],
                        cur.op.scale.d[2]
                ));
                break;
            }

            case POP: {
                cord_stack->pop();
                break;
            }

            case PUSH: {
                cord_stack->push();
                break;
            }

            case SAVE_COORDS: {
                //cord_stack->peek()->print_self();
                s->lookup_symbol(cur.op.save_coordinate_system.p->name)->s.m = cord_stack->peek();
                //s->add_symbol(cur.op.save_coordinate_system.p->name, SYM_MATRIX, cord_stack->peek());
                break;
            }

                // lighting

                // add a new light source to the current light source list
            case LIGHT: {
                //std::cout << "new light source" << std::endl;
                // remove the first light if this is a new light
                if (!custom_light) {
                    light_sources.erase(light_sources.begin()); // remove the default light
                    custom_light = true;
                }

                auto new_light = (double **) std::malloc(sizeof(double **) * 2);
                new_light[0] = (double *) std::malloc(sizeof(double *) * 3);
                new_light[1] = (double *) std::malloc(sizeof(double *) * 3);
                new_light[0][0] = cur.op.light.p->s.l->l[0];
                new_light[0][1] = cur.op.light.p->s.l->l[1];
                new_light[0][2] = cur.op.light.p->s.l->l[2];
                new_light[1][0] = cur.op.light.p->s.l->c[0];
                new_light[1][1] = cur.op.light.p->s.l->c[1];;
                new_light[1][2] = cur.op.light.p->s.l->c[2];;
                normalize_in_place(new_light[0]);

                light_sources.push_back(new_light);

                break;
            }

                // set new ambient color
            case AMBIENT: {
                ambient.r = cur.op.ambient.c[0];
                ambient.g = cur.op.ambient.c[1];
                ambient.b = cur.op.ambient.c[2];
                break;
            }

            case DISPLAY: {
                drawer->display();
                break;
            }

            case SAVE: {

                drawer->save(cur.op.save.p->name, "dummy");
                break;
            }

                // stuff we don't need to do anything for since the parser and lexer do it for us
            case CONSTANTS:
                break;

                // mesh
            case MESH: {
                auto parser = new OBJFileParser(cur.op.mesh.name);
                triangle_matrix = parser->get_triangle_matrix();
                triangle_matrix->apply_transformation(cord_stack->peek());
                if (cur.op.mesh.constants != nullptr)
                    drawer->draw_polygons(triangle_matrix, light_sources, &ambient, cur.op.mesh.constants->s.c);
                else
                    drawer->draw_polygons(triangle_matrix, light_sources, &ambient, default_constants);

                triangle_matrix->clear();

                //yeah
                break;
            }

                // default case (this means the command isn't implemented)
            default: {
                printf("Command with opcode [%d] is not yet implemented\n", cur.opcode);
                break;
            }
        }
    }
}
