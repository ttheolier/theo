import math

def mmm(lst):
    #for median
    lst.sort()
    if len(lst) % 2 == 0:
        median1 = lst[int(len(lst) /2)]
        median2 = lst[int(len(lst)/2 -1)]
        print('The median is ' + str(median1) +' or ' + str(median2) )
    else:
        median = lst[int(math.floor(len(lst)/2))]
        print('The median is ' + str(median)  )
    #for mean
    tot = 0
    for num in lst:
        tot += num
    mean = tot/len(lst)
    rnd = int(input('To how many decimal places would you like to round the mean? '))
    rndmean = round(mean, rnd)
    print('The mean is ' + str(rndmean)  )
    #for mode
    #modelst = [lst.count(num) for num in lst]  #old way of finding mode, would only work with one mode 
    #mode = lst[modelst.index(max(modelst))]
    #print('The mode is ' + str(mode) + '.')
    occ = 0
    modelst = []
    for num in lst:
        lst.count(num)
        if lst.count(num) < occ:
            continue
        elif lst.count(num) > occ:
            occ = lst.count(num)
            modelst = []
            modelst.append(num)
        elif lst.count(num) == occ and modelst.count(num) == 0:
            modelst.append(num)
    print('The mode is ' + str(modelst) + '.')
        
numlst = []
loop = 1
while loop == 1:
    try:
        newnum = float(input('Input a number you would like to add to the list, when finished input \"stop" '))
        numlst.append(newnum)
    except ValueError:
        break
    
mmm(numlst)


    
    

        

        
        