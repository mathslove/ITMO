def AntiQuickSort(data, n):
    for i in range(2, n):
        data[i], data[i // 2] = data[i // 2], data[i]


fi = open("antiqs.in", "r")
fo = open("antiqs.out", "w")

n = int(fi.readline())

data = []
for i in range(n):
    data.append(i+1)

AntiQuickSort(data, n)

for i in range(n):
    fo.write(str(data[i]) + " ")

fi.close()
fo.close()
