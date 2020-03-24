fo = open("sortland.in")
fi = open("sortland.out", 'w')

n = int(fo.readline())
a = fo.readline().split()
a = [a, []]
print(a)
for x in range(n):
    a[0][x] = float(a[0][x])
    a[1].append(x+1)

print(a)

for x in range(1, n):
    k = x
    while (k > 0) and (a[0] [k-1] > a[0] [k]):
        a[1][k], a[1][k - 1] = a[1][k - 1], a[1][k]
        a[0][k], a[0][k - 1] = a[0][k - 1], a[0][k]
        k -= 1

print(a)

fi.write(str(a[1][0]) + ' ' + str(a[1][n // 2]) + ' ' + str(a[1][n-1]))

fi.close()
fo.close()