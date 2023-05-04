#include <iostream>
#include "structer.hpp"
//#include "generating_data.hpp"
#include "function.hpp"
#include "benchmark.hpp"
#include <arm_neon.h>
//#include <opencv2/opencv.hpp>

void print_matrx(float32_t* A, int N, int M){
    for(int i = 0; i < N; i++){
	for(int j = 0; j < M; j++){
	    std::cout << A[i*M + j] << ' ';
	}
        std::cout << std::endl;
    }
}

//using namespace cv;

int main(){
    Image<bgr> a(1,1);
    float32_t* A = new float32_t[360000];
    float32_t* B = new float32_t[360000];
    float32_t* C = new float32_t[360000];


    void(*q)(float32_t*, int, int) = print_matrx;

    Benchmark<void(*)(float32_t*, float32_t*, float32_t*, int, int, int), float32_t*, float32_t*, float32_t*, int, int, int> b(matrix_multiply_2x2_neon_float, A, B, C, 600, 600, 600);
    //Benchmark<void(*)(float32_t*, int, int), float32_t*, int, int> b(print_matrx, A, 10, 10);
    b.run();
    b.info();
    ///Benchmark b(&Image<bgr>::readPicture, a, "GRN.BMP");
    //b.setName("Image reading");
    //b.run();
    //b.info();

    //std::cout <<image;
    return 0;
}
