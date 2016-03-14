#include <fstream>
#include <iostream>
#include <set>

using namespace std;

int main(int argc, const char* argv[])
{
    ifstream input(argv[1]);

    int num_ints{}; char delim{};
    string line;
    while (input >> num_ints >> delim && delim == ';')
    {
//         cout << "Loading " << num_ints << " values" << endl;
        set<int> numbers;
//         numbers.reserve(num_ints);
        for (int i = num_ints; i; --i)
        {
            if (i != num_ints) { input >> delim; }
            int number{};
            if (input >> number)
            {
//                 cout << "checking " << number << endl;
                if (!numbers.insert(number).second)
                {
                    cout << number << endl;
                    std::getline(input, line);
                    break;
                }
            }
        }
    }

    exit(0);
}
