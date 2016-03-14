#!/usr/bin/python3

import sys
test_cases = open(sys.argv[1], 'r')
for test in test_cases:
    value = int(test)
    count = 0
    # Start with 5
    remainder = value%5
    count += (value - remainder)/5
    # Move to 3
    remainder3 = remainder % 3
    count += (remainder - remainder3)/3
    # End with 1
    count += remainder3
    print(int(count))
    
test_cases.close()
