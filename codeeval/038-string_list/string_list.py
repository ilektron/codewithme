#!/usr/bin/python3

#
#   Created by Stephen Farnsworth
#

import sys
import itertools

test_cases = open(sys.argv[1], 'r')
for line in test_cases:
    test_case = line.rstrip().split(',')
    permutations = itertools.product(test_case[1], repeat=int(test_case[0]))
    answer = list()
    for item in permutations:
        answer.append(str().join(item))
    answer = set(answer)
    answer = list(answer)
    answer.sort()
    print(','.join(answer))
    
test_cases.close
