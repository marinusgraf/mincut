#include "karger.h"

int main(int argc, char** argv)
{
    
    if (argc != 2) 
    {
        std::cout << "invalid or no input path" << std::endl;
        exit(EXIT_FAILURE);
    }
    Graph g = file_to_graph(std::string{argv[1]});
    /*
    int n = g.n;
    long reps = log(n) * log(n) + 1;
    int nb_threads = std::thread::hardware_concurrency();
    long reps_per_thread = std::ceil(reps / nb_threads) + 1;
    std::atomic<int> min_cut{INT_MAX};
    std::thread threads[nb_threads];
    for (int i = 0; i < nb_threads; ++i)
    {
        threads[i] = std::thread{thread_work, karger_stein, g, reps_per_thread, std::ref(min_cut)};
    }
    for (int i = 0; i < nb_threads; ++i)
    {
        threads[i].join();
    }
    std::cout << min_cut << std::endl;
    */
    std::cout << karger_stein(g) << std::endl;
}