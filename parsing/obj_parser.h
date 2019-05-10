//
// Created by Ivan Galakhov on 2019-02-28.
//

#ifndef WORK_01_LINE_OBJ_PARSER_H
#define WORK_01_LINE_OBJ_PARSER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "../settings.h"
#include "../matrix/edge_matrix.h"
#include "../matrix/triangle_matrix.h"

class OBJFileParser {
public:
    OBJFileParser(std::string);
    ~OBJFileParser();

    EdgeMatrix * get_edge_matrix();
    TriangleMatrix * get_triangle_matrix();


private:
    void parse_file();
    std::string file_name;
    std::vector<float_mat *> vertex_list;
    std::vector<int *> face_list;

};


#endif //WORK_01_LINE_OBJ_PARSER_H
