#include <queue>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>


using std::cout;
using std::endl;
using std::string;

enum class op_type
{
    none,
    match,
    substitution,
    indel1,
    indel2
};

int check_score(std::string gene1, std::string gene2)
{
    int score{};
    
    gene1 = " " + gene1;
    gene2 = " " + gene2;
    
    return score;
}

int main(int argc, const char* argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    std::ifstream input(argv[1]);

    string gene1, gene2, delim;
    while (input >> gene1 >> delim >> gene2 && delim == "|")
    {
        auto score = check_score(gene1, gene2);
        std::cout << score << std::endl;
    }

    return 0;
}