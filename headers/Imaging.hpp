#ifndef _IMAGING_
#define _IMAGING_
#include "Structer.hpp"

class Color {
private:
    unsigned char c[3];
public:
    Color(unsigned char r_m = 0, unsigned char g_m = 0, unsigned char b_m = 0);     // constructor
    Color(const Color& color_m);                                                    // copy constructor

    ~Color() {}                                                                     // destructor

    Color& operator=(const Color& color_m);                                         // assignment operator
    Color& operator=(const unsigned char& char_m);                                  
    unsigned char& R();                                                             
    const unsigned char& R() const;
    unsigned char& G();
    const unsigned char& G() const;
    unsigned char& B();
    const unsigned char& B() const;
    void set_color(unsigned char r_m, unsigned char g_m, unsigned char b_m);

    friend std::ostream& operator<<(std::ostream& out, const Color& color_m);
};

using Image = Mtrx<Color>;

#endif