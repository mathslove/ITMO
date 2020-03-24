f0 = open("aplusb.in",'r')
f1 = open("aplusb.out",'w')

a = 0
b = 0

a, b = (f0.read().split())

f1.write(str(int(a) + int(b)))
f0.close()
f1.close()