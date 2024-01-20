#include "edmonds_karp.hpp"

int main(int argc, char** argv)
{
    if (argc != 2) 
    {
        std::cout << "invalid input" << std::endl;
        exit(EXIT_FAILURE);
    }
    Graph g = file_to_graph(std::string{argv[1]});
    int n = g.partition.sets;
    long reps = (n * n * log(n));
    int nb_threads = std::thread::hardware_concurrency();
    long reps_per_thread = std::ceil(reps / nb_threads) + 1;
    std::atomic<int> min_cut{INT_MAX};
    std::thread threads[nb_threads];
    for (int i = 0; i < nb_threads; ++i)
    {
        threads[i] = std::thread{thread_work, karger, g, reps_per_thread, std::ref(min_cut)};
    }
    for (int i = 0; i < nb_threads; ++i)
    {
        threads[i].join();
    }
    std::cout << min_cut << std::endl;
}