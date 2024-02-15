#include <time.h>
#include <iostream>
#include <iomanip>

template <typename T>
void time_function(int (*func)(T g), T &g, int reps = 1)
{
    clock_t start, end;
    int result = INT_MAX;
    start = clock();
    for (int k = 0; k < reps; ++k)
    {
        result = std::min(result, func(g));
    }
    end = clock();
    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    std::cout << std::setprecision(3) << time_taken << ", "
    << result << std::endl;
}