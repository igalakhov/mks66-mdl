//
// Created by Ivan Galakhov on 2019-05-10.
//

#ifndef WORK_01_LINE_SYMBOL_TABLE_H
#define WORK_01_LINE_SYMBOL_TABLE_H

#include <iostream>

#include "../matrix/transformation_matrix.h"
#include "../settings.h"

#define MAX_SYMBOLS 512
#define SYM_MATRIX 1
#define SYM_VALUE 2
#define SYM_CONSTANTS 3
#define SYM_LIGHT 4
#define SYM_FILE   5
#define SYM_STRING 5

#define AMBIENT_R 0
#define DIFFUSE_R 1
#define SPECULAR_R 2

// symbol table structures
struct constants
{
    double r[4];
    double g[4];
    double b[4];
    double red,green,blue;
};

struct light
{
    double l[4];
    double c[4];
};

typedef struct
{
    char * name;
    int type;
    union {
        TransformationMatrix * m;
        struct constants * c;
        struct light * l;
        double val;
    } s;

} SYMBOL;

// symbol table class
// used for keeping track of (you guessed it!) symbols!

class SymbolTable {
public:
    SymbolTable();
    ~SymbolTable();

    SYMBOL * lookup_symbol(const char *);
    SYMBOL * add_symbol(const char *, int, void *);
    void print();


private:
    SYMBOL * symtab; // actual list of symbols
    int lastsym; // number of symbols

    void print_constants(struct constants *);
    void print_light(struct light *);
};


#endif //WORK_01_LINE_SYMBOL_TABLE_H
