#include <iostream>
#include <fstream>

int fib(int n)
{
    if (n <= 0)
    {
        return 0;
    }
    else if (n == 1)
    {
        return 1;
    }
    else
    {
        return fib(n - 1) + fib(n - 2);
    }
}

int main(int argc, const char* argv[])
{
    std::ifstream file(argv[1]);
    int num{};
    while (file >> num)
    {
        std::cout << fib(num) << std::endl;
    }
}
