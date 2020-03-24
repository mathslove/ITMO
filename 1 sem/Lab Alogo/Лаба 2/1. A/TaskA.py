def merge_sort(m: list):
    if len(m) == 1:
        return m
    mid = len(m) // 2
    L = m[0:mid]
    R = m[mid:len(m)]
    merge_sort(L)
    merge_sort(R)

    i = j = k = 0
    while j < len(R) and i < len(L):
        if L[i] < R[j]:
            m[k] = L[i]
            i += 1
        else:
            m[k] = R[j]
            j += 1
        k += 1

    while j < len(R) and i == len(L):
        m[k] = R[j]
        j += 1
        k += 1

    while i < len(L) and j == len(R):
        m[k] = L[i]
        i += 1
        k += 1


sortin = "sort.in"
sortout = "sort.out"
fi = open("sort.in", )
fo = open("sort.out", "w")

n = int(fi.readline())
data = [int(x) for x in fi.readline().split()]

merge_sort(data)

for i in range(0, n - 1):
    fo.write(str(data[i]) + ' ')
fo.write(str(data[n - 1]))

fi.close()
fo.close()