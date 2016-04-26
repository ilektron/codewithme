#include <fstream>
#include <iostream>
#include <string>

int main(int argc, const char* argv[])
{
    std::ifstream input(argv[1]);
    
    std::string line;
    while(std::getline(input, line))
    {
        std::size_t next_space = line.rfind(' ');
        std::size_t last_space = line.length();
        while (next_space != std::string::npos)
        {
            std::cout << line.substr(next_space + 1, last_space - next_space - 1) << ' ';
            last_space = next_space;
            next_space = line.rfind(' ', next_space - 1);
        }
        std::cout << line.substr(0, last_space) << std::endl;
    }
}
