import time

def pythagchecker(a,b,c):
    if a ** 2 + b ** 2 == c ** 2:
        return('This is a Pythagorean Triple')
    elif a ** 2 + c ** 2 == b ** 2:
        return('This is a Pythagorean Triple')
    elif b ** 2 + c ** 2 == a ** 2:
        return('This is a Pythagorean Triple')
    else:
        return('This is not a Pythagorean Triple')

loop = 'yes'
while loop == 'yes':
    side1 = int(input('Side 1?'))
    side2 = int(input('Side 2?'))
    side3 = int(input('Side 3?'))
    print(pythagchecker(side1,side2,side3))
    run_again = input('Do you have another triangle to check? yes or no?: ')
    if run_again == 'yes' or run_again == 'Yes':
        print('Resetting...')
        print()
        print()
        time.sleep(2)
    elif run_again == 'no' or run_again == 'No':
        print('Have a nice day!')
        loop = 'Stop'
    else:
        print("Couldn't understand your input... Sorry.")
        loop = 'Stop'
        