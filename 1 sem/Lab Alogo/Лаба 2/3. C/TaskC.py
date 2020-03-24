def mod_merge(massivchik: list):
    global result
    if len(massivchik) > 1:
        mid = (len(massivchik)+1)//2
        L = massivchik[0:mid]
        R = massivchik[mid:len(massivchik)]
        mod_merge(R)
        mod_merge(L)

        i = j = k = 0
        while i < len(L) and j < len(R):
            if L[i] <= R[j]:
                massivchik[k] = L[i]
                i += 1
            else:
                massivchik[k] = R[j]
                j += 1
                result += len(L)-i
            k += 1

        while i < len(L):
            massivchik[k] = L[i]
            k += 1
            i += 1

        while j < len(R):
            massivchik[k] = R[j]
            k += 1
            j += 1


fin = open("inversions.in", "r")
fout = open("inversions.out", "w")

n = int, fin.readline().split()
data = [int(x) for x in fin.readline().split()]
result = 0

mod_merge(data)

fout.write(str(result))
fin.close()
fout.close()
