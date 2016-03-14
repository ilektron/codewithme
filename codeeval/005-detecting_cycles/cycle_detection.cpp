//
//  Created by Stephen Farnsworth
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

void cycle_detection(string line)
{
    stringstream input(line);
    vector<int> tokens(50);
    map<int, int> previous_tokens;
    int token;
    while (input >> token)
    {
        auto found = previous_tokens.find(token);
        if (found == previous_tokens.end())
        {
            previous_tokens[token] = tokens.size();
            tokens.push_back(token);
        }
        else
        {
            cout << token;
            auto pos = found->second;
            while (input >> token && tokens[++pos] == token)
            {
                cout << " " << token;
            }

            cout << endl;
            break;
        }
    }
}

int main(int argc, const char* argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    ifstream input(argv[1]);

    string line;
    while (getline(input, line))
    {
        cycle_detection(line);
    }
}
