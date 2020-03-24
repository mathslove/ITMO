def merge_sort(m: list):
    if len(m) > 1:
        mid = (len(m)+1) // 2
        L = m[0:mid]
        R = m[mid:len(m)]
        merge_sort(R)
        merge_sort(L)

        i = j = k = 0
        while j < len(R) and i < len(L):
            if L[i][0] <= R[j][0]:
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

fi = open("race.in", 'r')
n = int(fi.readline())
data = []
for y in range(n):
    data.append([])
    data[y].extend(fi.readline().split())

merge_sort(data)

fo = open("race.out", 'w')

i = 0
while i < n:
    fo.write("=== "+str(data[i][0])+" ===\n")
    fo.write(data[i][1] + "\n")
    j = i + 1
    while j < n:
        if data[i][0] == data[j][0]:
            fo.write(data[j][1] + "\n")
            i = j
            j += 1
        else:
            break
    i += 1


fo.close()
