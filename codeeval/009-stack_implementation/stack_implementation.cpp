#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

int main(int argc, const char* argv[])
{
    std::string line;
    std::ifstream input(argv[1]);
    std::vector<int> stack;
    while (std::getline(input, line))
    {
        std::stringstream input_string(line);
        int val{};
        while (input_string >> val)
        {
            stack.push_back(val);
        }
        
        std::cout << stack.back();
        
        while (stack.size())
        {
            stack.pop_back();
            
            if (stack.size())
            {
                stack.pop_back();
                if (stack.size()) { std::cout << " " << stack.back(); }
            }
        }
        
        std::cout << std::endl;
    }
}