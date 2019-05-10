//
// Created by Ivan Galakhov on 2019-02-28.
//

#ifndef WORK_01_LINE_SCRIPT_PARSER_H
#define WORK_01_LINE_SCRIPT_PARSER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "../../matrix/transformation_matrix.h"
#include "../../matrix/edge_matrix.h"
#include "../../matrix/triangle_matrix.h"
#include "../../drawing/drawer.h"
#include "../../drawing/parametric/parametric.h"
#include "../../drawing/3d/3d.h"
#include "coordinate_stack.h"

class MDLParser {
public:
    // constructor/destructor
    explicit MDLParser(std::string);
    ~MDLParser();

    // running the file
    void run_file(EdgeMatrix *, TriangleMatrix *, TransformationMatrix *, Drawer *);
    void run_file(); // le empty

private:
    std::string file_name;

    void ltrim(std::string&);
    void rtrim(std::string&);
    void trim(std::string&);

    std::vector<std::string> split_string(std::string);
};


#endif //WORK_01_LINE_SCRIPT_PARSER_H
