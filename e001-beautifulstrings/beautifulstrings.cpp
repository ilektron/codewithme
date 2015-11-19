#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <array>
#include <cctype>

int main(int argc, const char* argv[])
{
	if (argc != 2)
	{
		return 1;
	}

	std::ifstream input(argv[1]);

	std::string line;

	while (std::getline(input, line))
	{
		std::array<int,26> counted_chars{};
		
		for (auto c : line)
		{
			if (std::isalpha(c))
			{
				counted_chars[std::tolower(c) - 'a']++;
			}
		}

		std::sort(counted_chars.begin(), counted_chars.end());

		int point_value = 1;
		int beautiful_value = 0;
		for (auto num_chars : counted_chars)
		{
			beautiful_value += num_chars * point_value;
			point_value++;
		}

		std::cout << beautiful_value << std::endl;
	}

	return 0;
}
