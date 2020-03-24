f0 = open("smallsort.in")
f1 = open("smallsort.out", 'w')

n = int(f0.readline())
a = f0.readline().split()
for i in range(n):
    a[i] = int(a[i])
print(a)

for i in range(1, n):
    k = i
    while (k > 0) and (a[k-1] > a[k]):
        a[k], a[k - 1] = a[k - 1], a[k]
        k -= 1

for i in range(n-1):
    f1.write(str(a[i])+' ')
f1.write(str(a[n-1]))

f0.close()
f1.close()