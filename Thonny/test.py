import sys

def systest(y):
    if y == 1:
        sys.exit()
        
x = input('input number ')

loop = 'loopy'
while loop == 'loopy':
    x = input('input number ')
    systest(x)