#ifndef _COLOR_
#define _COLOR_
#include <iostream>
enum mode { rgb, bgr };

template <mode Mode>
class Color {
private:
    unsigned char components[4];
public:

    Color(const unsigned char& a = 0, const unsigned char& b = 0, const unsigned char& c = 0, const unsigned char& d = 0);
    Color(const Color& color_m);

    ~Color() {}

    Color& operator=(const Color& color_m);
    Color& operator=(const unsigned char& char_m);

    unsigned char& R();
    const unsigned char& R() const;
    unsigned char& G();
    const unsigned char& G() const;
    unsigned char& B();
    const unsigned char& B() const;
    unsigned char& A();
    const unsigned char& A() const;
    void set_color(const unsigned char& a = 0, const unsigned char& b = 0, const unsigned char& c = 0, const unsigned char& d = 0);
    unsigned char* getComp();
    friend std::ostream& operator<<(std::ostream& out, const Color& color_m);
};

template <mode Mode>
Color<Mode>::Color(const unsigned char& a, const unsigned char& b, const unsigned char& c, const unsigned char& d)
{
    components[0] = a;
    components[1] = b;
    components[2] = c;
    components[3] = d;
} /*-------------------------------------------------------------------------*/

template <mode Mode>
Color<Mode>::Color(const Color& color_m) {
    components[0] = color_m.components[0];
    components[1] = color_m.components[1];
    components[2] = color_m.components[2];
    components[3] = color_m.components[3];
} /*-------------------------------------------------------------------------*/

template <mode Mode>
Color<Mode>& Color<Mode>::operator=(const Color<Mode>& color_m) {
    components[0] = color_m.components[0];
    components[1] = color_m.components[1];
    components[2] = color_m.components[2];
    components[3] = color_m.components[3];
    return *this;
} /*-------------------------------------------------------------------------*/

template <mode Mode>
Color<Mode>& Color<Mode>::operator=(const unsigned char& char_m) {
    components[0] = char_m;
    components[1] = char_m;
    components[2] = char_m;
    components[3] = char_m;
    return *this;
} /*-------------------------------------------------------------------------*/

template <>
unsigned char& Color<mode::rgb>::R() {
    return components[0];
} /*-------------------------------------------------------------------------*/

template <>
const unsigned char& Color<mode::rgb>::R() const{
    return components[0];
} /*-------------------------------------------------------------------------*/

template <>
unsigned char& Color<mode::bgr>::R() {
    return components[2];
} /*-------------------------------------------------------------------------*/

template <>
const unsigned char& Color<mode::bgr>::R() const {
    return components[2];
} /*-------------------------------------------------------------------------*/

template <mode Mode>
unsigned char& Color<Mode>::G() {
    return components[1];
} /*-------------------------------------------------------------------------*/

template <mode Mode>
const unsigned char& Color<Mode>::G() const {
    return components[1];
} /*-------------------------------------------------------------------------*/

template <>
unsigned char& Color<mode::rgb>::B() {
    return components[2];
} /*-------------------------------------------------------------------------*/

template <>
const unsigned char& Color<mode::rgb>::B() const {
    return components[2];
} /*-------------------------------------------------------------------------*/

template <>
unsigned char& Color<mode::bgr>::B() {
    return components[0];
} /*-------------------------------------------------------------------------*/

template <>
const unsigned char& Color<mode::bgr>::B() const {
    return components[0];
} /*-------------------------------------------------------------------------*/

template <mode Mode>
unsigned char& Color<Mode>::A() {
    return components[3];
} /*-------------------------------------------------------------------------*/

template <mode Mode>
const unsigned char& Color<Mode>::A() const {
    return components[3];
} /*-------------------------------------------------------------------------*/

template <>
void Color<mode::rgb>::set_color(const unsigned char& a, const unsigned char& b, const unsigned char& c, const unsigned char& d) {
    components[0] = a;
    components[1] = b;
    components[2] = c;
    components[3] = d;
} /*-------------------------------------------------------------------------*/

template <>
void Color<mode::bgr>::set_color(const unsigned char& a, const unsigned char& b, const unsigned char& c, const unsigned char& d) {
    components[0] = c;
    components[1] = b;
    components[2] = a;
    components[3] = d;
} /*-------------------------------------------------------------------------*/

template <mode Mode>
unsigned char* Color<Mode>::getComp(){
    unsigned char* a = new unsigned char[4];
    a[0] = components[0];
    a[1] = components[1];
    a[2] = components[2];
    a[3] = components[3];
    return a;
}

std::ostream& operator<<(std::ostream& out, const Color<mode::rgb>& color_m) {
    out << (int)color_m.R() << ',' << (int)color_m.G() << ',' << (int)color_m.B();
    return out;
}

std::ostream& operator<<(std::ostream& out, const Color<mode::bgr>& color_m) {
    out << (int)color_m.B() << ',' << (int)color_m.G() << ',' << (int)color_m.R();
    return out;
}
#endif