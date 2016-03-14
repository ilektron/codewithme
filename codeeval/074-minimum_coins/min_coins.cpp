//
//  Created by Stephen Farnsworth
//

#include <iostream>
#include <fstream>

int main(int argc, const char* argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    std::ifstream input(argv[1]);
    int value = 0;
    while (input >> value)
    {
        int count = 0;
        int remainder5 = value % 5;
        count += (value - remainder5)/5;
        int remainder3 = remainder5 % 3;
        count += (remainder5 - remainder3)/3;
        count += remainder3;
        std::cout << count << std::endl;
    }
    
    return 0;
}
