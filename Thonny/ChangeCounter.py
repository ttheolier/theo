import math

def change_counter(money, price):
    change_amt = money - price
    amtofq = 0
    amtofd = 0
    amtofn = 0
    amtofp = 0
    if change_amt >= .25:
        amtofq = math.floor(change_amt/.25)
        change_amt = round(change_amt - amtofq * .25,2)
        if change_amt >= .10:
            amtofd = math.floor(change_amt/.10)
            change_amt = round(change_amt-amtofd * .10,2)
        if change_amt >= .05:
            amtofn = math.floor(change_amt/.05)
            change_amt = round(change_amt- amtofn * .05,2)
        if change_amt >= .01:
            print(change_amt)
            amtofp = math.floor(change_amt/.01)
            change_amt = round(change_amt-amtofp * .01,2)
        print(str(amtofq) + ' Quarters, ' + str(amtofd) + ' Dimes, ' + str(amtofn) + ' Nickels, ' + str(amtofp) + ' Pennies.')
    elif change_amt >= .10:
        amtofd = math.floor(change_amt/.10)
        change_amt = round(change_amt-amtofd * .10,2)
        if change_amt >= .05:
            amtofn = math.floor(change_amt/.05)
            change_amt = round(change_amt-amtofn * .05,2)
        if change_amt >= .01:
            amtofp = math.floor(change_amt/.01)
            change_amt = round(change_amt-amtofp * .01,2)
        print(str(amtofq) + ' Quarters, ' + str(amtofd) + ' Dimes, ' + str(amtofn) + ' Nickels, ' + str(amtofp) + ' Pennies.')
    elif change_amt >= .05:
        amtofn = math.floor(change_amt/.05)
        change_amt = round(change_amt-(amtofn * .05),2)
        if change_amt >= .01:
            amtofp = math.floor(change_amt/.01)
            change_amt = round(change_amt-amtofp * .01,2)
        print(str(amtofq) + ' Quarters, ' + str(amtofd) + ' Dimes, ' + str(amtofn) + ' Nickels, ' + str(amtofp) + ' Pennies.')
    elif change_amt >= .01:
        amtofp = math.floor(change_amt/.01)
        change_amt += -amtofp * .01
        print(str(amtofq) + ' Quarters, ' + str(amtofd) + ' Dimes, ' + str(amtofn) + ' Nickels, ' + str(amtofp) + ' Pennies.')
    elif change_amt == 0:
        print('No Change')

loop = 'loop'


while loop == 'loop':
    cash = float(input('How much cash was given by the customer? '))
    total = float(input('What was the customer\'s total? '))
    change_counter(cash, total)






