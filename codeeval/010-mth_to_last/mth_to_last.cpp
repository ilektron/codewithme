#include <fstream>
#include <iostream>

int main(int argc, const char* argv[])
{
    std::ifstream input(argv[1]);

    std::string line;
    while (std::getline(input, line))
    {

    }

    return 0;
}
