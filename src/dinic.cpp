#include "dinic.h"

int main(int argc, char** argv)
{
    if (argc != 2) 
    {
        std::cout << "invalid input" << std::endl;
        exit(EXIT_FAILURE);
    }
    Graph g = file_to_adjmat(std::string{argv[1]});
    std::cout << dinic(g) << std::endl;
    
}