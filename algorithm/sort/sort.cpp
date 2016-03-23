#include <algorithm>
#include <iostream>
#include <vector>

// This is a custom class that we can use in order to demonstrate the operator< in std::sort
struct value
{
    value(int i_) : i{i_} {}
    bool operator<(value v) { return i < v.i; }
    int i;
};

// Helper function to print our custom class
std::ostream& operator<<(std::ostream& os, const value& v)
{
    os << v.i;
    return os;
}

// Helper function to output a vector of integers
template <class T>
void print_vector(const T& v)
{
    bool comma = false;
    std::cout << '{';
    for (const auto& val : v)
    {
	if (comma) { std::cout << ','; }
	comma = true;
	std::cout << val;
    }
    std::cout << '}' << std::endl;
}

int main(int argc, const char* argv[])
{
    // Sort integers
    {
	std::vector<int> data = {2, 3, 1, 6, 3, 5};
	std::sort(data.begin(), data.end());
	std::cout << "Sorted integers: ";
	print_vector(data);
    }
    // Custom less than function
    {
	std::vector<int> data = {2, 3, 1, 6, 3, 5};
	std::sort(data.begin(), data.end(), [](int lhs, int rhs){ return lhs > rhs; });
	std::cout << "Sorted integers with >: ";
	print_vector(data);
    }
    // Reverse iterators
    {
	std::vector<int> data = {2, 3, 1, 6, 3, 5};
	std::sort(data.rbegin(), data.rend());
	std::cout << "Reverse sorted integers: ";
	print_vector(data);
    }
    // Partial Sort
    {
	std::vector<int> data = {2, 3, 1, 6, 3, 5};
	std::sort(data.begin(), data.begin() + 3);
	std::cout << "Partially sorted integers: ";
	print_vector(data);
    }
    // Sort strings
    {
	std::vector<std::string> data = {"This", "is", "a", "sentence", "that", "we'll", "sort.", "Sort", "me!"};
	std::sort(data.begin(), data.end());
	std::cout << "Sorted strings: ";
	print_vector(data);
    }
    // Sort custom class
    {
	std::vector<value> data = {2, 3, 1, 6, 3, 5};
	std::sort(data.begin(), data.end());
	std::cout << "Sorted custom class: ";
	print_vector(data);
    }
    return 0;
}

