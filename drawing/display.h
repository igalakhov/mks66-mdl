#include <iostream>
#include <cassert>
#include "../settings.h"

#ifndef WORK_01_LINE_DISPLAY_H
#define WORK_01_LINE_DISPLAY_H

class Display {
public:
    void save(std::string, std::string);  // save into file
    void display(); // display self (requires imagemagik with x11)

    Display(); // constructor
    ~Display(); // destructor

    void set(int, int, float_mat, struct color *); // set a pixel to a value
    void clear();


protected:

private:
    unsigned char * values; // pixel values (1d array because I'm cool)
    float_mat * z_buffer;

};


#endif //WORK_01_LINE_DISPLAY_H
