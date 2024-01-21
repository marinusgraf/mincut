#include "stoer_wagner.hpp"

int main(int argc, char** argv)
{
    if (argc != 2) 
    {
        std::cout << "invalid input" << std::endl;
        exit(EXIT_FAILURE);
    }
    auto e = file_to_adjmat(std::string{argv[1]});
    std::cout << stoer_wagner(e) << std::endl;
}