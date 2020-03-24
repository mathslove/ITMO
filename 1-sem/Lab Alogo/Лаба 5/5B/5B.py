def put(k, x1, x2):
    if hash_f[k] is not None:
        f = 0
        for i in range(len(hash_f[k])):
            if hash_f[k][i][0] == x1:
                hash_f[k][i][1] = x2
                f = 1
                break
        if f == 0:
            hash_f[k].append([x1, x2])
    else:
        hash_f[k] = []
        hash_f[k].append([x1, x2])


def delete(k, x1):
    if hash_f[k] is not None:
        if len(hash_f[k]) == 0:
            hash_f[k] = None
            return
        for i in range(len(hash_f[k])):
            if hash_f[k][i][0] == x1:
                hash_f[k][i], hash_f[k][len(hash_f[k])-1] = hash_f[k][len(hash_f[k])-1], hash_f[k][i]
                hash_f[k].pop()
                break



def get(k, x1):
    if hash_f[k] is not None:
        for i in range(len(hash_f[k])):
            if hash_f[k][i][0] == x1:
                return hash_f[k][i][1]
    return "none"


fi = open("map.in")
fo = open("map.out", "w")

P = 32
hash_f = [None] * 1000000
data = []
for line in fi:
    data = line.split()

    k = 0
    i = 0
    for el in data[1]:
        k += (ord(el) % 97 + 1)*(P**i)
        i += 1
    k %= 10**6

    if data[0] == "put":
        put(k, data[1], data[2])
    elif data[0] == "delete":
        delete(k, data[1])
    elif data[0] == "get":
        print(get(k, data[1]), file=fo)

fi.close()
fo.close()
