#!/usr/bin/python3

#
#   Created by Stephen Farnsworth
#

import sys

def solve_case(seed, pieces):
    
    while len(pieces):
        initial_size = len(pieces)
        for piece in pieces:
            #print 'Seed:\'' + seed + '\'\tPiece: \'' + piece + '\''
            #print 'checking \'' + seed[:len(piece) - 1] + '\' against \'' + piece[1:] + '\''
            # Check if the piece precedes our block
            if seed[:len(piece) - 1] == piece[1:]:
                #print '-------------------' + piece
                seed = piece[:1] + seed
                #print seed
                pieces.remove(piece)
                break
            
            #print 'checking \'' + seed[-len(piece) + 1:] + '\' against \'' + piece[:-1] + '\''
            # Check if the comes after our block
            if seed[-len(piece) + 1:] == piece[:-1]:
                #print '-------------------' + piece
                seed += piece[-1:]
                #print seed
                pieces.remove(piece)
                break
            
        if initial_size == len(pieces):
            #print 'Failed to glue'
            return False
    print(seed)
    return True
    

test_cases = open(sys.argv[1], 'r')
for line in test_cases:
    
    pieces = list(filter(None, line.strip('\n').split('|')))
    seed = pieces.pop(-1)
    #print 'Starting with ' + seed
    pieces_copy = pieces[:]
    while not solve_case(seed, pieces_copy):
        #print 'Trying ' + seed
        #print pieces
        pieces.insert(0, seed)
        seed = pieces.pop(-1)
        pieces_copy = pieces[:]
        

