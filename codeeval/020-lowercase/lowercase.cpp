//
//  Created by Stephen Farnsworth
//

#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>

int main(int argc, const char* argv[])
{
    if (argc != 2) { return 1; }

    std::fstream input(argv[1]);
    std::string line;
    while (std::getline(input, line))
    {
        for (char c : line) { std::cout << static_cast<char>(tolower(c)); }
        std::cout << std::endl;
    }
}
