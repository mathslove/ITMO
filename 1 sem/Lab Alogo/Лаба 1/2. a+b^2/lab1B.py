f0 = open("aplusbb.in",'r')
f1 = open("aplusbb.out",'w')

a = 0
b = 0

a, b = (f0.read().split())

f1.write(str(int(a) + int(b)**2))
f0.close()
f1.close()