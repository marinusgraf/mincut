#include <time.h>
#include <iostream>
#include <iomanip>

template <typename T>
void time_function(int (*func)(T &g), T &g, int reps = 1)
{
    clock_t start, end;
    start = clock();
    int result = func(g);
    end = clock();
    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    std::cout << std::setprecision(3) << time_taken * reps<< ", "
    << result << std::endl;
}