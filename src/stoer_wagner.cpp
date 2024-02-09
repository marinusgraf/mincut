#include "stoer_wagner.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "invalid input" << std::endl;
        exit(EXIT_FAILURE);
    }
    Graph g =file_to_graph(std::string{argv[1]});
    std::cout << stoer_wagner(g) << std::endl;
}