#include <iostream>
#include <fstream>
#include <algorithm>

int main(int argc, const char* argv[])
{
    std::ifstream input_file(argv[1]);
    std::string line;
    while (std::getline(input_file, line))
    {
        auto permutation = line;
        if (std::next_permutation(permutation.begin(), permutation.end()))
        {
            std::cout << permutation << std::endl;
        }
        else
        {
            permutation.insert(permutation.begin(), '0');
            line.insert(line.begin(), '0');
            while (permutation.compare(line) <= 0 && std::next_permutation(permutation.begin(), permutation.end()))
            {
                // nop
            }
            std::cout << permutation << std::endl;
        }
    }
    
    return 0;
}