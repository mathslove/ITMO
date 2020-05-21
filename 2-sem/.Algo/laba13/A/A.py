fi = open("search1.in", "r")
fo = open("search1.out", "w")

bulavka = fi.readline().strip()
seno = fi.readline().strip()

c = 0
res = []

for i in range(len(seno)-len(bulavka)+1):
    t = seno[i:i+len(bulavka)]
    if t == bulavka:
        res.append(i+1)
        c += 1

fo.write(str(c)+'\n')
for x in res:
    fo.write(str(x)+' ')

fi.close()
fo.close()