#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, const char* argv[])
{
    if (argc != 2)
    {
        exit(1);
    }

    ifstream input(argv[1]);
    
    string line;
    while (std::getline(input, line))
    {
        sort(line.begin(), line.end());
        vector<string> perms;
        do
        {
            perms.push_back(line);
        } while (next_permutation(line.begin(), line.end()));

        sort(perms.begin(), perms.end());
        bool comma = false;
        for (auto perm : perms)
        {
            if (comma) { cout << ","; }
            cout << perm;
            comma = true;
        }
        cout << endl;
    }

    exit(0);
}
