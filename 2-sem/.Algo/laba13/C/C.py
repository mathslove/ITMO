def buildP(T):
    n = len(T)
    i = 1
    j = 0
    while i < n:
        if T[i] == T[j]:
            pi[i+1] = j+1
            i += 1
            j += 1
        elif j > 0:
            j = pi[j]
        else:
            pi[i+1] = 0
            i+=1


fi = open("prefix.in", "r")
fo = open("prefix.out", "w")

string = list(fi.readline().strip())
n = len(string)
pi = [0 for _ in range(n+1)]
pi[0] = None

buildP(string)

for i in range(1, n+1):
    fo.write(str(pi[i])+" ")

fi.close()
fo.close()
