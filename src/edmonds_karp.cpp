#include "edmonds_karp.hpp"

int main(int argc, char** argv)
{
    if (argc != 2) 
    {
        std::cout << "invalid input" << std::endl;
        exit(EXIT_FAILURE);
    }
    auto e = file_to_adjmat(std::string{argv[1]});
    std::cout << edmonds_karps(e) << std::endl;
}