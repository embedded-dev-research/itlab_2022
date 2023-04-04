#include <iostream>
#include "Structer.hpp"
#include "data_render.hpp"
#include "Function.hpp"
#include "Color.hpp"

int main(){
    Image<bgr> a(10, 10);
    Image<rgb> b(10,10);
    std::cout << a;
    return 0;
}