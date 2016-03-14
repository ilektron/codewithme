//
//  Created by Stephen Farnsworth
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>

int main(int argc, const char* argv[])
{
    std::ifstream input(argv[1]);
    std::string line;
    while (std::getline(input, line))
    {
        auto comma = line.find(',');
        auto value = atoi(line.c_str());
        std::string base = line.substr(comma + 1);
        std::cout << value << ":" << base << std::endl;
        std::set<std::string> results;
        std::sort(base.begin(), base.end());
        
        for
        {
        }
        
        std::cout << "Result: ";
        for (const auto& thing : results)
        {
            std::cout << thing << ",";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
