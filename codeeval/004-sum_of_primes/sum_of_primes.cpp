#include <cmath>
#include <stdio.h>

bool is_prime(int val)
{
    int sqrt = std::sqrt(val);
    for (int j = sqrt; j > 1; --j)
    {
        if ((val % j) == 0)
        {
            return false;
        }
    }

    return true;
}

int main(int argc, const char* argv[])
{
    int sum = 2;
    int count = 2;
    for (int i = 3; count <= 1000; i+=2)
    {
        if (is_prime(i))
        {
            sum += i;
            count++;
        }
    }

    printf("%d\n", sum);
    return 0;
}
