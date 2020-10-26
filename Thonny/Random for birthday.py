import random
list = []
for n in range (23):
    x = int(random.randint(1,366))
    if x in list:
        print ("done")
    else:
        list.append(x)
    print(x)