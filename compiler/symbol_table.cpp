//
// Created by Ivan Galakhov on 2019-05-10.
//

#include "symbol_table.h"


void SymbolTable::print() {
    int i;
    for (i = 0; i < lastsym; i++) {
        std::printf("Name: %s\n", symtab[i].name);
        switch (symtab[i].type) {
            case SYM_MATRIX:
                printf("Type: SYM_MATRIX\n");
                symtab[i].s.m->print_self();
                break;
            case SYM_CONSTANTS:
                printf("Type: SYM_CONSTANTS\n");
                print_constants(symtab[i].s.c);
                break;
            case SYM_LIGHT:
                printf("Type: SYM_LIGHT\n");
                print_light(symtab[i].s.l);
                break;
            case SYM_VALUE:
                printf("Type: SYM_VALUE\n");
                printf("value: %6.2f\n", symtab[i].s.val);
                break;
            case SYM_FILE:
                printf("Type: SYM_VALUE\n");
                printf("Name: %s\n", symtab[i].name);
            default:
                break;
        }
        printf("\n");
    }
}

SYMBOL *SymbolTable::add_symbol(const char *name, int type, void *data) {

    SYMBOL *t;

    t = (SYMBOL *) lookup_symbol(name);
    if (t == nullptr) {
        if (lastsym >= MAX_SYMBOLS) {
            return nullptr;
        }
        t = (SYMBOL *) &(symtab[lastsym]);
        lastsym++;
    } else {
        return t;
    }

    t->name = (char *) malloc(strlen(name) + 1);
    strcpy(t->name, name);
    t->type = type;
    switch (type) {
        case SYM_CONSTANTS:
            t->s.c = (struct constants *) data;
            break;
        case SYM_MATRIX:
            t->s.m = (TransformationMatrix *) data;
            break;
        case SYM_LIGHT:
            t->s.l = (struct light *) data;
            break;
        case SYM_VALUE: {
            if(data == nullptr)
                t->s.val = 0;
            else
                t->s.val = *((double *) data);
            break;
        }
        case SYM_FILE:
            break;

        default:
            break;
    }
    return (SYMBOL *) &(symtab[lastsym - 1]);

}

SYMBOL *SymbolTable::lookup_symbol(const char *name) {
    int i;
    for (i = 0; i < lastsym; i++) {
        if (!strcmp(name, symtab[i].name)) {
            return &(symtab[i]);
        }
    }
    return (SYMBOL *) nullptr;
}

// initalize
SymbolTable::SymbolTable() {
    symtab = (SYMBOL *) std::malloc(MAX_SYMBOLS * sizeof(SYMBOL));

}

// destruct
SymbolTable::~SymbolTable() {
    std::free(symtab);
}


// print light
void SymbolTable::print_light(struct light *p) {
    std::printf("Location -\t %6.2f %6.2f %6.2f\n",
                p->l[0], p->l[1], p->l[2]);

    std::printf("Brightness -\t r:%6.2f g:%6.2f b:%6.2f\n",
                p->c[0], p->c[1], p->c[2]);
}

// print light
void SymbolTable::print_constants(struct constants *p) {
    std::printf("\tRed -\t  Ka: %6.2f Kd: %6.2f Ks: %6.2f\n",
                p->r[0], p->r[1], p->r[2]);

    std::printf("\tGreen -\t  Ka: %6.2f Kd: %6.2f Ks: %6.2f\n",
                p->g[0], p->g[1], p->g[2]);

    std::printf("\tBlue -\t  Ka: %6.2f Kd: %6.2f Ks: %6.2f\n",
                p->b[0], p->b[1], p->b[2]);

    std::printf("Red - %6.2f\tGreen - %6.2f\tBlue - %6.2f\n",
                p->red, p->green, p->blue);
}