#ifndef _COLOR_
#define _COLOR_
#include <iostream>
enum layout { rgb, bgr };

template <layout Layout>
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

template <layout Layout>
Color<Layout>::Color(const unsigned char& a, const unsigned char& b, const unsigned char& c, const unsigned char& d)
{
    components[0] = a;
    components[1] = b;
    components[2] = c;
    components[3] = d;
} /*-------------------------------------------------------------------------*/

template <layout Layout>
Color<Layout>::Color(const Color& color_m) {
    components[0] = color_m.components[0];
    components[1] = color_m.components[1];
    components[2] = color_m.components[2];
    components[3] = color_m.components[3];
} /*-------------------------------------------------------------------------*/

template <layout Layout>
Color<Layout>& Color<Layout>::operator=(const Color<Layout>& color_m) {
    components[0] = color_m.components[0];
    components[1] = color_m.components[1];
    components[2] = color_m.components[2];
    components[3] = color_m.components[3];
    return *this;
} /*-------------------------------------------------------------------------*/

template <layout Layout>
Color<Layout>& Color<Layout>::operator=(const unsigned char& char_m) {
    components[0] = char_m;
    components[1] = char_m;
    components[2] = char_m;
    components[3] = char_m;
    return *this;
} /*-------------------------------------------------------------------------*/

template <>
unsigned char& Color<layout::rgb>::R() {
    return components[0];
} /*-------------------------------------------------------------------------*/

template <>
const unsigned char& Color<layout::rgb>::R() const{
    return components[0];
} /*-------------------------------------------------------------------------*/

template <>
unsigned char& Color<layout::bgr>::R() {
    return components[2];
} /*-------------------------------------------------------------------------*/

template <>
const unsigned char& Color<layout::bgr>::R() const {
    return components[2];
} /*-------------------------------------------------------------------------*/

template <layout Layout>
unsigned char& Color<Layout>::G() {
    return components[1];
} /*-------------------------------------------------------------------------*/

template <layout Layout>
const unsigned char& Color<Layout>::G() const {
    return components[1];
} /*-------------------------------------------------------------------------*/

template <>
unsigned char& Color<layout::rgb>::B() {
    return components[2];
} /*-------------------------------------------------------------------------*/

template <>
const unsigned char& Color<layout::rgb>::B() const {
    return components[2];
} /*-------------------------------------------------------------------------*/

template <>
unsigned char& Color<layout::bgr>::B() {
    return components[0];
} /*-------------------------------------------------------------------------*/

template <>
const unsigned char& Color<layout::bgr>::B() const {
    return components[0];
} /*-------------------------------------------------------------------------*/

template <layout Layout>
unsigned char& Color<Layout>::A() {
    return components[3];
} /*-------------------------------------------------------------------------*/

template <layout Layout>
const unsigned char& Color<Layout>::A() const {
    return components[3];
} /*-------------------------------------------------------------------------*/

template <>
void Color<layout::rgb>::set_color(const unsigned char& a, const unsigned char& b, const unsigned char& c, const unsigned char& d) {
    components[0] = a;
    components[1] = b;
    components[2] = c;
    components[3] = d;
} /*-------------------------------------------------------------------------*/

template <>
void Color<layout::bgr>::set_color(const unsigned char& a, const unsigned char& b, const unsigned char& c, const unsigned char& d) {
    components[0] = c;
    components[1] = b;
    components[2] = a;
    components[3] = d;
} /*-------------------------------------------------------------------------*/

template <layout Layout>
unsigned char* Color<Layout>::getComp(){
    unsigned char* a = new unsigned char[4];
    a[0] = components[0];
    a[1] = components[1];
    a[2] = components[2];
    a[3] = components[3];
    return a;
}

std::ostream& operator<<(std::ostream& out, const Color<layout::rgb>& color_m) {
    out << (int)color_m.R() << ',' << (int)color_m.G() << ',' << (int)color_m.B();
    return out;
}

std::ostream& operator<<(std::ostream& out, const Color<layout::bgr>& color_m) {
    out << (int)color_m.B() << ',' << (int)color_m.G() << ',' << (int)color_m.R();
    return out;
}
#endif  // _COLOR_