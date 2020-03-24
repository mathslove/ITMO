def garland(x):
    global A
    global n
    b1 = A
    b2 = x
    for i in range(2, n):
        b3 = 2*(b2+1)-b1
        if b3 < 0:
            return True
        b1 = b2
        b2 = b3
    return False


fi = open("garland.in", "r")
fo = open("garland.out", "w")

tmp = fi.readline().split()
n = int(tmp[0])
A = float(tmp[1])

l = 0
r = A


while l+0.000001 < r:
    h2 = (l + r) / 2
    if garland(h2):
        l = h2
    else:
        r = h2
first = A
mid = l
last = 0

for i in range(2, n):
     last = 2*(mid+1) - first
     first = mid
     mid = last
B = last
print(round(B, 2), file=fo)

fi.close()
fo.close()
