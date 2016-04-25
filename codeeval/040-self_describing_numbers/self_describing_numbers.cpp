#include <iostream>
#include <fstream>
#include <string>
#include <array>

int main(int argc, const char* argv[])
{
    std::ifstream input_file(argv[1]);
    
    std::string line;
    while (std::getline(input_file, line))
    {
        std::array<int, 10> counts{};
        for (auto& c : line)
        {
            c -= '0';
            if (c < 10 && c >= 0)
            {
                counts[c]++;
            }
        }
        
        bool success = true;
        for (int i=0; i < std::min(10u, (unsigned int)line.length()); i++)
        {
            if (line[i] != counts[i])
            {
                std::cout << "0" << std::endl;
                success = false;
                break;
            }
        }
        if (success)
        {
            std::cout << "1" << std::endl;
        }
    }
}
