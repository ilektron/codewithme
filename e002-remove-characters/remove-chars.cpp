#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>

int main(int argc, const char* argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    std::ifstream input(argv[1]);

    std::string input_text;
    std::string bad_chars;
    while (std::getline(input, input_text, ',') && std::getline(input, bad_chars))
    {
        bad_chars.erase(std::remove(bad_chars.begin(), bad_chars.end(), ' '), bad_chars.end());

        auto begin_remove = std::remove_if(input_text.begin(), input_text.end(), 
            [&](char c)
            {
                bool should_remove = (bad_chars.find(c) != std::string::npos);
                return should_remove;
            });

        input_text.erase(begin_remove, input_text.end());

        std::cout << input_text << std::endl;
    }
}


