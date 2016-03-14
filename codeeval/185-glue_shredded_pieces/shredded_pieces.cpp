#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

deque<string> tokenize(const string& line, char delim)
{
    stringstream input(line);
    deque<string> tokens;
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

std::string build_message(deque<string> bucket, std::string seed = "")
{
//     cout << "Checking seed: " << seed << endl;
    std::string solution;
    if (bucket.size() <= 0)
    {
        return "";
    }

    if (seed.empty())
    {
        seed = bucket.back();
        bucket.pop_back();
    }

    size_t last_bucket_size{};
    while (bucket.size() != last_bucket_size)
    {
        std::vector<deque<string>::iterator> prefixes;
        std::vector<deque<string>::iterator> postfixes;
        last_bucket_size = bucket.size();

        for (auto itr = bucket.begin(); itr != bucket.end();)
        {
            auto& piece = *itr;
            if (equal(piece.begin() + 1, piece.end(), seed.begin()))
            {
                prefixes.push_back(itr);
            }
            else if (equal(piece.begin(), piece.end() - 1, seed.end() - piece.length() + 1))
            {
                postfixes.push_back(itr);
            }
            ++itr;
        }
        
        // Check to see if we have multiple solutions
        if (prefixes.size() > 1)
        {
            for (auto itr : prefixes)
            {
                // Add to beginning
                auto new_seed = itr->at(0) + seed;
                // Remove from bucket
                auto bucket_copy = bucket;
                bucket_copy.erase(std::find(bucket_copy.begin(), bucket_copy.end(), *itr));
                auto solution = build_message(bucket_copy, new_seed);
                if (!solution.empty())
                {
                    return solution;
                }
            }
        }
        else if (postfixes.size() > 1)
        {
            for (auto itr : postfixes)
            {
                // Add to beginning
                auto new_seed = seed;
                new_seed.push_back(itr->back());
                // Remove from bucket
                auto bucket_copy = bucket;
                bucket_copy.erase(std::find(bucket_copy.begin(), bucket_copy.end(), *itr));
                auto solution = build_message(bucket_copy, new_seed);
                if (!solution.empty())
                {
                    return solution;
                }
            }
        }
        else
        {
            if (prefixes.size() == 1)
            {
                auto itr = prefixes.back();
                // Add to beginning
                seed = itr->at(0) + seed;
                // Remove from bucket
                bucket.erase(itr);
            }
            else if (postfixes.size() == 1)
            {
                auto itr = postfixes.back();
                // Add to end
                seed.push_back(itr->back());
                // Remove from bucket
                bucket.erase(itr);
            }
        }
    }
    
    // Return the completed solution if we've used all the pieces
    return bucket.size() == 0 ? seed : "";
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
        if (!line.empty())
        {
            auto pieces = tokenize(line, '|');
            std::string solution = build_message(pieces);
            
            if (!solution.empty())
            {
                cout << solution << endl;
            }
        }
    }

    exit(0);
}
