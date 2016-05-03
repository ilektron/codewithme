#!/usr/bin/python3

#
#   Created by Stephen Farnsworth
#

def fib(n):
    if n <= 0:
        return 0
    elif n == 1:
        return 1
    else:
        return fib(n-1) + fib(n-2)


import sys
test_cases = open(sys.argv[1], 'r')
for test in test_cases:
    value = int(test)
    print(fib(value))
    
test_cases.close()
