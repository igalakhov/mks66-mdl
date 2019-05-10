//
// Created by Ivan Galakhov on 2019-02-28.
//

#include "mdl_parser.h"

void MDLParser::run_file(EdgeMatrix * edge_matrix, TriangleMatrix * triangle_matrix,  TransformationMatrix * transformation_matrix, Drawer * drawer) {
    std::ifstream file(file_name);
    std::string str;

    std::vector<std::string> args;

    auto cstack = new CoordinateStack();

    while(std::getline(file, str)){
        trim(str);

        if(str == "display"){
            drawer->display();
        } else if(str == "scale"){
            std::getline(file, str);
            trim(str);
            args = split_string(str);

            cstack->apply_transformation(TransformationMatrix::dilation(
                    std::stof(args.at(0)),
                    std::stof(args.at(1)),
                    std::stof(args.at(2))
                    ));
        } else if(str == "translate" or str == "move"){
            std::getline(file, str);
            trim(str);
            args = split_string(str);

            cstack->apply_transformation(TransformationMatrix::translation(
                    std::stof(args.at(0)),
                    std::stof(args.at(1)),
                    std::stof(args.at(2))
            ));
        } else if(str == "rotate"){
            std::getline(file, str);
            trim(str);
            args = split_string(str);

            if(args.at(0) == "x"){
                cstack->apply_transformation(TransformationMatrix::rotationX(
                        std::stof(args.at(1))
                        ));
            }
            if(args.at(0) == "y"){
                cstack->apply_transformation(TransformationMatrix::rotationY(
                        std::stof(args.at(1))
                ));
            }
            if(args.at(0) == "z"){
                cstack->apply_transformation(TransformationMatrix::rotationZ(
                        std::stof(args.at(1))
                ));
            }
        } if(str == "line"){ // drawing
                std::getline(file, str);
                trim(str);
                args = split_string(str);

                edge_matrix->add_edge(std::stof(args.at(0)), std::stof(args.at(1)), std::stof(args.at(2)),
                            std::stof(args.at(3)), std::stof(args.at(4)), std::stof(args.at(5)));

                edge_matrix->apply_transformation(cstack->peek());
                drawer->draw_edges(edge_matrix);
                edge_matrix->clear();

        } else if(str == "circle"){
                std::getline(file, str);
                trim(str);
                args = split_string(str);

                add_circle(edge_matrix, std::stof(args.at(0)), std::stof(args.at(1)), std::stof(args.at(2)), std::stof(args.at(3)));

                edge_matrix->apply_transformation(cstack->peek());
                drawer->draw_edges(edge_matrix);
                edge_matrix->clear();

        } else if (str == "hermite") {
                std::getline(file, str);
                trim(str);
                args = split_string(str);

                add_hermite(edge_matrix, std::stof(args.at(0)),
                                std::stof(args.at(1)),
                                std::stof(args.at(2)),
                                std::stof(args.at(3)),
                                std::stof(args.at(4)),
                                std::stof(args.at(5)),
                                std::stof(args.at(6)),
                                std::stof(args.at(7)));

                edge_matrix->apply_transformation(cstack->peek());
                drawer->draw_edges(edge_matrix);
                edge_matrix->clear();


        } else if (str == "bezier") {
                std::getline(file, str);
                trim(str);
                args = split_string(str);

                add_bezier(edge_matrix, std::stof(args.at(0)),
                             std::stof(args.at(1)),
                             std::stof(args.at(2)),
                             std::stof(args.at(3)),
                             std::stof(args.at(4)),
                             std::stof(args.at(5)),
                             std::stof(args.at(6)),
                             std::stof(args.at(7)));

                edge_matrix->apply_transformation(cstack->peek());
                drawer->draw_edges(edge_matrix);
                edge_matrix->clear();

        } else if (str == "box"){
            std::getline(file, str);
            trim(str);
            args = split_string(str);

            add_box(triangle_matrix,
                    std::stof(args.at(0)),
                    std::stof(args.at(1)),
                    std::stof(args.at(2)),
                    std::stof(args.at(3)),
                    std::stof(args.at(4)),
                    std::stof(args.at(5)));

            triangle_matrix->apply_transformation(cstack->peek());
            drawer->draw_polygons(triangle_matrix);
            triangle_matrix->clear();

        } else if (str == "sphere"){
            std::getline(file, str);
            trim(str);
            args = split_string(str);

            add_sphere(triangle_matrix,
                    std::stof(args.at(0)),
                    std::stof(args.at(1)),
                    std::stof(args.at(2)),
                    std::stof(args.at(3)));

            triangle_matrix->apply_transformation(cstack->peek());
            drawer->draw_polygons(triangle_matrix);
            triangle_matrix->clear();

        } else if (str == "torus") {
            std::getline(file, str);
            trim(str);
            args = split_string(str);

            add_torus(triangle_matrix,
                      std::stof(args.at(0)),
                      std::stof(args.at(1)),
                      std::stof(args.at(2)),
                      std::stof(args.at(3)),
                      std::stof(args.at(4)));

            triangle_matrix->apply_transformation(cstack->peek());
            drawer->draw_polygons(triangle_matrix);
            triangle_matrix->clear();


        } else if(str == "save") { // saving and quitting
            std::getline(file, str);
            trim(str);
            args = split_string(str);

            drawer->save(args.at(0), ".ppm");
        } else if(str == "push"){
            cstack->push();
        } else if(str == "pop") {
            cstack->pop();
        }else if(str == "quit") {
            return;
        } else if(str == "clear"){
            drawer->clear();
        } else {
            continue;
            //throw std::invalid_argument("Invalid command [" + str + "]");
        }

//        cstack->print_stack();
//
//        std::cout << "\n ------------- \n";

    }
}

MDLParser::MDLParser(std::string file_name) {
    this->file_name = std::move(file_name);
}

MDLParser::~MDLParser(){
    // nothing here yet
}

// split string
std::vector<std::string> MDLParser::split_string(std::string str){
    std::string buf;
    std::stringstream ss(str);

    std::vector<std::string> tokens;

    while (ss >> buf)
        tokens.push_back(buf);

    return tokens;
}

void MDLParser::run_file(){
    run_file(new EdgeMatrix(), new TriangleMatrix(), TransformationMatrix::identity(), new Drawer());
}

// string trimming
void MDLParser::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

void MDLParser::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

void MDLParser::trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}
