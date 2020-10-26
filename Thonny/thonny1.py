#This function takes in a height, weight and age and responds back whether or not this person can ride
def sixflags(height,weight,age): #height in inches, weight in pounds
    if height >= 60 and weight <=300 and age >= 15:
        print('All Good!')
    elif not height >= 60 and weight <= 300 and age >= 15:
        print('Get out of here midget!')
    elif height >= 60 and not weight <= 300 and age >= 15:
        print('Calm down on the eating buddy!')
    elif height >= 60 and weight <= 300 and not age >= 15:
        print("Sorry dawg you're too little")
    else:
        print('Get your life togather before you go to Six Flags next time.')

#sixflags(55,400,19) #Test Program, all works

#Function take price of up to four items and returns total including tax
def totalprice(item1=0,item2=0,item3=0,item4=0):
    subtotal = item1+item2+item3+item4
    total = 1.08 * subtotal
    return total

#print(str(totalprice(4,9,18))) #Test worked.

#Function takes in number randomly assigned by variable and spits out a combo
import random
thairand = random.randint(1,3)
def thaicombo(num):
    if num == 1:
        print("jab, cross, hook")
    if num == 2:
        print('double jab, low right, check hook, body kick')
    if num == 3:
        print('rear teap, rear teap, jab, jab, question mark')

#thaicombo(thairand) #test worked.
        
import time

def timetest(name):
    print('Loading.')
    time.sleep(1)
    print('Loading..')
    time.sleep(1)
    print('Loading...')
    time.sleep(1)
    print('Welcome ' + name + '!')
    
#timetest('Thomalina')

