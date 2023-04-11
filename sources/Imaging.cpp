#include "Imaging.hpp"

/// 
/// class Color
/// 

Color::Color(unsigned char r_m, unsigned char g_m, unsigned char b_m) // constructor
{
    c[0] = r_m;
    c[1] = g_m;
    c[2] = b_m;
} /*-------------------------------------------------------------------------*/

Color::Color(const Color& color_m) :
    Color(color_m.R(), color_m.G(), color_m.B()) {}

Color& Color::operator=(const Color& color_m) // assignment
{
    c[0] = color_m.R();
    c[1] = color_m.G();
    c[2] = color_m.B();

    return *this;
} /*-------------------------------------------------------------------------*/

Color& Color::operator=(const unsigned char& char_m) {
    c[0] = char_m;
    c[1] = char_m;
    c[2] = char_m;

    return *this;
} /*-------------------------------------------------------------------------*/

unsigned char& Color::R() {
    return c[0];
} /*-------------------------------------------------------------------------*/
const unsigned char& Color::R() const {
    return c[0];
} /*-------------------------------------------------------------------------*/

unsigned char& Color::G() {
    return c[1];
} /*-------------------------------------------------------------------------*/

const unsigned char& Color::G() const {
    return c[1];
} /*-------------------------------------------------------------------------*/

unsigned char& Color::B() {
    return c[2];
} /*-------------------------------------------------------------------------*/

const unsigned char& Color::B() const {
    return c[2];
} /*-------------------------------------------------------------------------*/

void Color::set_color(unsigned char r_m, unsigned char g_m, unsigned char b_m) {
    c[0] = r_m;
    c[1] = g_m;
    c[2] = b_m;
} /*-------------------------------------------------------------------------*/


std::ostream& operator<<(std::ostream& out, const Color& color_m) // output
{
    out << (int)color_m.R() << ',' << (int)color_m.G() << ',' << (int)color_m.B();

    return out;
} /*-------------------------------------------------------------------------*/