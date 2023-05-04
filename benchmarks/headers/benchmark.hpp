#ifndef _BENCHMARK_
#define _BENCHMARK_

#include <functional>
#include <vector>
#include <string>
#include <iostream>
#include "timer.hpp"
#include <arm_neon.h>

template <typename Func, typename ...Arg>
class Benchmark{
private:
    int m_count;      				// number of iterations of the measurement
    std::string m_name;				// function benchmark name
    std::function<void()> m_func;		// pointer to the function to be measured
    double exec_time;    			// arithmetic mean of function execution time (seconds)
public:
    Benchmark(Func func, Arg... args);

    void setIterations(int count);		// sets the number of benchmark iterations
    void setName(const std::string& name);	// sets the name of the benchmark
    void run();                                 // launch benchmark
    void info();				// output of benchmark information
};


template <typename Func, typename ...Arg>
Benchmark<Func, Arg...>::Benchmark(Func func, Arg... args)
    : m_count(10)
    , m_name("Some function")
    , exec_time(-1)
{
    m_func = std::bind(func, args...);
}

template <typename Func, typename ...Arg>
void Benchmark<Func, Arg...>::setIterations(int count){
    m_count = count;
}

template <typename Func, typename ...Arg>
void Benchmark<Func, Arg...>::setName(const std::string& name){
    m_name = name;
}

template <typename Func, typename ...Arg>
void Benchmark<Func, Arg...>::run(){
    double total_time = 0;
    for(int i = 0; i < m_count; i++){
	Timer t;
	m_func();
	t.stop();
        total_time += t.duration_s();
    }
    exec_time = total_time/m_count;
}

template <typename Func, typename ...Arg>
void Benchmark<Func, Arg...>::info(){
    std::cout << "  " << m_name << std::endl;
    std::cout << "===========================" << std::endl;
    std::cout << "Timer:  " << exec_time << "  seconds" << std::endl;
}

#endif // _BENCHMARK_
