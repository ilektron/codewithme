#!/usr/bin/python3

#
#   Created by Stephen Farnsworth
#

text_under20 = ['', 'One', 'Two', 'Three', 'Four', 'Five', 'Six', 'Seven', 'Eight', 'Nine', 'Ten', 'Eleven', 'Twelve', 'Thirteen', 'Fourteen', 'Fifteen', 'Sixteen', 'Seventeen', 'Eighteen', 'Nineteen']
text_tens = ['', 'Ten', 'Twenty', 'Thirty', 'Forty', 'Fifty', 'Sixty', 'Seventy', 'Eighty', 'Ninety']
text_hundred = 'Hundred'
text_powers = ['', 'Thousand', 'Million', 'Billion', 'Trillion']


def one_to_thousand(n):
    text = ''
    if n >= 100:
        text = text_under20[int(n/100)] + text_hundred
    n = n % 100
    if n >= 20:
        text = text + text_tens[int(n/10)]
        n = n % 10
    text = text + text_under20[int(n)]
    return text

def dollars(n):
    if n == 0:
        return 'ZeroDollars'
    #if n == 1:
        #return 'OneDollar'
    
    text = 'Dollars'
    powers = 0;
    while n > 0:
        remainder = n % 1000
        if remainder > 0:
            text = one_to_thousand(remainder) + text_powers[powers] + text
        n = int(n/1000)
        powers += 1
    return text
        


import sys
test_cases = open(sys.argv[1], 'r')
for test in test_cases:
    try:
        value = int(test)
        print(dollars(value))
    except:
        pass
    
test_cases.close()
