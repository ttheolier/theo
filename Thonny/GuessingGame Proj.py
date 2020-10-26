import random


def guessing_game(guess, random):
    #loop = 1
    #while loop == 1:
    global tries
    global loop2
    if guess > random:
        print('Too High')
        tries += 1
    elif guess < random:
        tries += 1
        print('Too Low')
    elif guess == random:
        print('Good Stuff, took you ' + str(tries + 1 ) + ' tries!.')
        loop2 = 0
        if tries > 10:
            print('Patience was key...')
        

loop1 = 1
loop2 = 1
print('The name of the game is guess the random number from 0 to 100, if you guess it correctly, its over, if you don\'t, I\'ll let you know if you guessed too high or too low. Have Fun!')
while loop1 == 1:
    tries = 0
    random1 = random.randint(0,10)
    while loop2 == 1:
        guess1 = int(input('Guess a number. '))
        guessing_game(guess1,random1)
    question = input('Do you want to play again? ')
    if question == 'no' or question == 'No':
        print('See Ya!')
        loop1 = 0
    elif question == 'yes':
        print('Restarting')
        print()
        loop2 = 1
              
            
    
