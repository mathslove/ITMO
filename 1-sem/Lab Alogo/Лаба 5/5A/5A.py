def insert(x):
    k = abs(x) % 262419
    if hash_f[k] is None:
        hash_f[k] = []
        hash_f[k].append(x)
    elif not (x in hash_f[k]):
        hash_f[k].append(x)


def delete(x):
    k = abs(x) % 262419
    if hash_f[k] is not None:
        if x in hash_f[k]:
            hash_f[k].remove(x)
    if hash_f[k] == []:
        hash_f[k] = None


def exists(x):
    k = abs(x) % 262419
    if hash_f[k] is not None:
        if x in hash_f[k]:
            return True
        else:
            return False
    else:
        return False


fi = open("set.in")
fo = open("set.out", "w")

hash_f = [None] * 262419
data = []
for line in fi:
    data = line.split()
    data[1] = int(data[1])
    if data[0] == "insert":
        insert(data[1])
    elif data[0] == "delete":
        delete(data[1])
    elif data[0] == "exists":
        if exists(data[1]):
            print("true", file=fo)
        else:
            print("false", file=fo)

fi.close()
fo.close()