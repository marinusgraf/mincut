#include "karger.h"
#include "timer.h"

int main(int argc, char** argv)
{
    
    if (argc != 2) 
    {
        std::cout << "invalid input" << std::endl;
        exit(EXIT_FAILURE);
    }
    Graph g = file_to_graph(std::string{argv[1]});
    int reps = g.n * g.n * log(g.n) + 1;
    time_function<Graph>(karger, g, reps);
}