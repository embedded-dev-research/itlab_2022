#include <iostream>
#include "structer.hpp"
#include "generating_data.hpp"
#include "function.hpp"
#include "color.hpp"
#include "bmp.hpp"
#include "timer.hpp"

int main(){
    Image<rgb> a(10,10,Color<rgb>(123,124,5));
    int b = 0;
    Timer t;
    
    t.start();
    for(int i = 0; i < 10000; i++){
        b+= 10;
    }
    t.stop();
    std::cout << "Duration_s: " << t.duration_s();

    return 0;
}