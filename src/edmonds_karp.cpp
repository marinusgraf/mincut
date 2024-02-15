#include "edmonds_karp.h"
#include "timer.h"

int main(int argc, char** argv)
{
    if (argc != 2) 
    {
        std::cout << "invalid input" << std::endl;
        exit(EXIT_FAILURE);
    }
    Network g = file_to_network(std::string{argv[1]});
    //st_maxflow(g, 0, 4);
    time_function(edmonds_karp, g);
}