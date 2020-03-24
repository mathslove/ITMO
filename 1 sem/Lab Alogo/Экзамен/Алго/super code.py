import random

fo = open("test.txt", "w")

n = 1000

for i in range(n):
    k = random.randint(1,4)
    if k==1:
        print("+", random.randint(-1000000000,1000000000), file=fo)
    elif k == 2:
        print("-", random.randint(-1000000000, 1000000000), file=fo)
    elif k == 3:
        print(">", random.randint(-1000000000, 1000000000), file=fo)
    elif k == 4:
        print(">", random.randint(-1000000000, 1000000000), file=fo)

fo.close()