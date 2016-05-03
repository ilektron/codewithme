//
//  Created by Stephen Farnsworth
//

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::equal;
using std::vector;
using std::getline;
using std::stringstream;

inline vector<string> tokenize(const string& line, char delim)
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

inline std::string build_message(vector<string>& bucket)
{
    std::string solution;
    if (bucket.size() <= 0)
    {
        return "";
    }
    
    auto piece_size = bucket.back().length();
    
    while (bucket.size() > 1)
    {
        auto size_before = bucket.size();
        for (auto itr = bucket.begin(); itr != bucket.end();)
        {
            auto match = bucket.end();
            
            auto compare_string = itr->substr(itr->length() - (piece_size - 1));
//             std::cout << "Comparing: '" << compare_string << "'" << std::endl;
            auto found = std::lower_bound(bucket.begin(), bucket.end(), compare_string);
            auto first_found = bucket.end();
            while (found != bucket.end() && equal(compare_string.begin(), compare_string.end(), found->begin()))
            {
                if (found != itr)
                {
                    if (first_found == bucket.end())
                    {
                        match = first_found = found;
                    }
                    else if (*first_found != *found)
                    {
                        match = found;
                        break;
                    }
                }
                found++;
            }
            
            if (match != bucket.end() && match == first_found)
            {
                // Add to beginning
//                 std::cout << "Changing '" << *itr;
                itr->append(first_found->substr(piece_size - 1));
                // Remove from bucket
//                 std::cout << "' to '" << *itr << "'" << endl;
                itr = bucket.erase(first_found);
            }
            else
            {
                // Multiple solutions
                itr++;
            }
        }
        if (size_before == bucket.size())
        {
            // We have duplicates that match, join them
            auto dup = std::adjacent_find(bucket.begin(), bucket.end(), [=](const std::string& s1, const std::string& s2){ return std::equal(s1.begin() + 1, s1.begin() + piece_size, s2.begin());});
            if (dup != bucket.end())
            {
                dup->push_back(dup->back());
                bucket.erase(dup + 1);
                continue;
            }
            else
            {
                std::cout << "Fail! No dups!" << std::endl;
                for (auto& chunk : bucket)
                {
                    std::cout << chunk << endl;
                }
                break;
            }
        }
    }
    
    // Return the completed solution if we've used all the pieces
    return bucket.size() == 1 ? bucket.back() : "";
}

int main(int argc, const char* argv[])
{
    if (argc != 2)
    {
        exit(1);
    }

    std::ifstream input(argv[1]);

    string line;
    while (std::getline(input, line))
    {
        if (!line.empty())
        {
            auto pieces = tokenize(line, '|');
            std::sort(pieces.begin(), pieces.end());
            std::string solution = build_message(pieces);
            
            if (!solution.empty())
            {
                printf("%s\n", solution.c_str());
//                 cout << solution << endl;
            }
        }
    }

    exit(0);
}
