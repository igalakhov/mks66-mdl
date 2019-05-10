//
// Created by Ivan Galakhov on 2019-02-28.
//

#include "obj_parser.h"

TriangleMatrix * OBJFileParser::get_triangle_matrix(){
    auto ret = new TriangleMatrix();

    for(int * i : face_list){
        float_mat * v0 = vertex_list.at(i[0] - 1);
        float_mat * v1 = vertex_list.at(i[1] - 1);
        float_mat * v2 = vertex_list.at(i[2] - 1);

        ret->add_triangle(
                v0[0], v0[1], v0[2],
                v1[0], v1[1], v1[2],
                v2[0], v2[1], v2[2]);
    }

    return ret;
}

EdgeMatrix * OBJFileParser::get_edge_matrix(){
    auto ret = new EdgeMatrix();

    for(int * i : face_list){
        float_mat * v0 = vertex_list.at(i[0] - 1);
        float_mat * v1 = vertex_list.at(i[1] - 1);
        float_mat * v2 = vertex_list.at(i[2] - 1);

        ret->add_edge(v0[0], v0[1], v0[2], v1[0], v1[1], v1[2]);
        ret->add_edge(v0[0], v0[1], v0[2], v2[0], v2[1], v2[2]);
        ret->add_edge(v2[0], v2[1], v2[2], v1[0], v1[1], v1[2]);
    }

    return ret;
}

// constructor
OBJFileParser::OBJFileParser(std::string file_name){
    std::ifstream file(file_name);
    std::string str;

    std::vector<float_mat *> vertex_list;
    std::vector<int *> face_list;


    // iterate line by line, splitting each line by space
    while (std::getline(file, str)){
        std::string buf;
        std::stringstream ss(str);

        std::vector<std::string> tokens;

        while (ss >> buf)
            tokens.push_back(buf);

        if(tokens.empty())
            continue;

        // only look at vertex and faces now
        if(tokens.at(0) == "v") {
            vertex_list.push_back(new float_mat[3]{std::stof(tokens.at(1)), std::stof(tokens.at(2)), std::stof(tokens.at(3))});
        }
        if(tokens.at(0) == "f"){
            face_list.push_back(new int[3]{std::stoi(tokens.at(1)), std::stoi(tokens.at(2)), std::stoi(tokens.at(3))});
        }
    }

    // assign values
    this->vertex_list = vertex_list;
    this->face_list = face_list;
}

// destructor
OBJFileParser::~OBJFileParser() {
    // nothing here yet I guess
}