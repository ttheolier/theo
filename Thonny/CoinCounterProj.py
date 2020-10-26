import math
import time
import sys

def startpointG(coin, weight):
    if coin == 'penny':
        pennies = weight / 2.5
        pwraps = pennies / 50
        pwraps1 = math.ceil(pwraps)
        evp = pennies * .01
        print('You have about ' + str(int(round(pennies, 0))) + ' pennies and will need ' + str(pwraps1) + ' coin wrapper(s).')
        print('Estimated Value: $' + str(round(evp, 2)))
    elif coin == 'nickel':
        nickels = weight / 5
        nwraps = nickels / 40
        nwraps1 = math.ceil(nwraps)
        evn = nickels * .05
        print('You have about ' + str(int(round(nickels, 0))) + ' nickels and will need ' + str(nwraps1) + ' coin wrapper(s).')
        print('Estimated Value: $' + str(round(evn, 2)))
    elif coin == 'dime':
        dimes = weight / 2.268
        dwraps= dimes / 50
        dwraps1 = math.ceil(dwraps)
        evd = dimes * .1
        print('You have about ' + str(int(round(dimes, 0))) + ' dimes and will need ' + str(dwraps1) + ' coin wrapper(s).')
        print('Estimated Value: $' + str(round(evd, 2)))
    elif coin == 'quarter':
        quarters = weight / 5.67
        qwraps = quarters / 40
        qwraps1 = math.ceil(qwraps)
        evq = quarters * .2
        print('You have about ' + str(int(round(quarters, 0))) + ' quarters and will need ' + str(qwraps1) + ' coin wrapper(s).')
        print('Estimated Value: $' + str(round(evq, 2)))
    else:
        print("Sorry, couldn't understand your input...")
        
def startpointP(coin, weight):
    if coin == 'penny':
        pennies = weight / .00551
        pwraps = pennies / 50
        pwraps1 = math.ceil(pwraps)
        evp = pennies * .01
        print('You have about ' + str(int(round(pennies, 0))) + ' pennies and will need ' + str(pwraps1) + ' coin wrapper(s).')
        print('Estimated Value: $' + str(round(evp, 2)))
    elif coin == 'nickel':
        nickels = weight / .011
        nwraps = nickels / 40
        nwraps1 = math.ceil(nwraps)
        evn = nickels * .05
        print('You have about ' + str(int(round(nickels, 0))) + ' nickels and will need ' + str(nwraps1) + ' coin wrapper(s).')
        print('Estimated Value: $' + str(round(evn, 2)))
    elif coin == 'dime':
        dimes = weight / .005
        dwraps= dimes / 50
        dwraps1 = math.ceil(dwraps)
        evd = dimes * .1
        print('You have about ' + str(int(round(dimes, 0))) + ' dimes and will need ' + str(dwraps1) + ' coin wrapper(s).')
        print('Estimated Value: $' + str(round(evd, 2)))
    elif coin == 'quarter':
        quarters = weight / .0125
        qwraps = quarters / 40
        qwraps1 = math.ceil(qwraps)
        evq = quarters * .2
        print('You have about ' + str(int(round(quarters, 0))) + ' quarters and will need ' + str(qwraps1) + ' coin wrapper(s).')
        print('Estimated Value: $' + str(round(evq, 2)))
    else:
        print("Sorry, couldn't understand your input...")
        

loop = 'looping'

PreliminaryQ = input('Is your coin weight in grams or pounds? ')
if PreliminaryQ == 'pounds' or PreliminaryQ == 'Pounds':
    while loop == 'looping':
        if PreliminaryQ == 'pounds' or PreliminaryQ == 'Pounds':
            C = input('What Kind of coin is this? Options: penny, nickel, dime, quarter: ')
            W = float(input('What is the weight of the coins in pounds?: '))
            startpointP(C,W)
            run_again = input('More coins to input, yes or no? ')
            if run_again == 'yes' or run_again == 'Yes':
                print('Resetting Program, Please Wait...')
                time.sleep(1)
            elif run_again == 'no' or run_again == 'No':
                loop = 'done'
                print('Thank you! See you again soon!')
            else:
                loop = 'done'
                print("Didn't understand, Shutting Down.")

    #print('No support for this yet, but coming soon!') (this and next line from when pounds was not finished)
    #sys.exit()
elif PreliminaryQ == 'grams' or PreliminaryQ == 'Grams':
    while loop == 'looping':
        if PreliminaryQ == 'grams' or PreliminaryQ == 'Grams':
            C = input('What Kind of coin is this? Options: penny, nickel, dime, quarter: ')
            W = float(input('What is the weight of the coins in grams?: '))
            startpointG(C,W)
            run_again = input('More coins to input, yes or no? ')
            if run_again == 'yes' or run_again == 'Yes':
                print('Resetting Program, Please Wait...')
                time.sleep(1)
            elif run_again == 'no' or run_again == 'No':
                loop = 'done'
                print('Thank you! See you again soon!')
            else:
                loop = 'done'
                print("Didn't understand, Shutting Down.")

    
