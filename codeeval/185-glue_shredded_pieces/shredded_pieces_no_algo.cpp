//
//  Created by Stephen Farnsworth
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

bool equal_impl(string::iterator first1, string::iterator last1, string::iterator first2)
{
    for (; first1 != last1; ++first1, ++first2)
    {
        if (!(*first1 == *first2))
        {
            return false;
        }
    }
    return true;
}

vector<string> tokenize(const string& line, char delim)
{
    stringstream input(line);
    vector<string> tokens;
    string token;
    while (getline(input, token, delim))
    {
        if (token.length())
        {
            tokens.push_back(token);
        }
    }

    return tokens;
}

bool build_message(string seed, vector<string>& bucket)
{
    if (!bucket.size())
    {
        cout << seed << endl;
        return true;
    }
    else
    {
        if (seed == "")
        {
            seed = bucket.back();
            bucket.pop_back();
        }

        for (auto itr = bucket.begin(); itr != bucket.end(); itr++)
        {
            auto& piece = *itr;
            if (equal_impl(piece.begin() + 1, piece.end(), seed.begin()))
            {
                // Add to beginning
                seed = piece[0] + seed;
                // Remove from bucket
                bucket.erase(itr);
                return build_message(seed, bucket);
            }
            else if (equal_impl(piece.begin(), piece.end() - 1, seed.end() - piece.length() + 1))
            {
                // Add to end
                seed.push_back(piece.back());
                // Remove from bucket
                bucket.erase(itr);
                return build_message(seed, bucket);
            }
        }
    }
    return false;
}

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
        if (line.length() == 0)
            continue;
        auto pieces = tokenize(line, '|');
        auto bucket = pieces;
        while (!build_message("", bucket))
        {
            pieces.insert(pieces.begin(), pieces.back());
            pieces.pop_back();
            bucket = pieces;
        }
    }

    exit(0);
}
