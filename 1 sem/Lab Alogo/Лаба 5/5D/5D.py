def hashkey(x):
    k = 0
    for el in x:
        k = 31 * k + ord(el) % 97
    return k % 32469


def hashkeyS(x):
    k = 0
    for el in x:
        k = 31 * k + ord(el) % 97
    return k % 231


def add(a, y):
    if a:
        a.append(y)
    else:
        a = [y]
    return a


# -----------

def put(x, y):
    k = hashkey(x)
    pt = hashkeyS(y)
    if hashmap[k]:
        for i in range(len(hashmap[k])):
            if hashmap[k][i][0] == x:
                if hashmap[k][i][1][pt]:
                    for el in hashmap[k][i][1][pt]:
                        if el == y:
                            return
                hashmap[k][i][1][pt] = add(hashmap[k][i][1][pt], y)
                hashmap[k][i][2] += 1
                return
        LIST = [x, [None] * (231), 1]
        hashmap[k].append(LIST)
        hashmap[k][len(hashmap[k])-1][1][pt] = add(hashmap[k][len(hashmap[k])-1][1][pt], y)
    else:
        hashmap[k] = [[x, [None] * (231), 1]]
        hashmap[k][0][1][pt] = add(hashmap[k][0][1][pt], y)


def get(x):
    k = hashkey(x)
    s = ""
    if not (hashmap[k]):
        print(0, file=fo)
        return
    for el in hashmap[k]:
        if el[0] == x:
            for tmp in el[1]:
                if tmp:
                    for cur in tmp:
                        s += str(cur) + " "
            print(el[2], s, file=fo)
            return
    print(0, file=fo)


def delete(x, y):
    k = hashkey(x)
    pt = hashkeyS(y)
    if not (hashmap[k]):
        return
    for i in range(len(hashmap[k])):
        if hashmap[k][i][0] == x:
            if hashmap[k][i][1][pt]:
                for j in range(len(hashmap[k][i][1][pt])):
                    if hashmap[k][i][1][pt][j] == y:
                        del hashmap[k][i][1][pt][j]
                        hashmap[k][i][2] -= 1
                        if hashmap[k][i][2] == 0:
                            del hashmap[k][i]
                        break
            break


def deleteall(x):
    k = hashkey(x)
    if hashmap[k]:
        for i in range(len(hashmap[k])):
            if hashmap[k][i][0] == x:
                del hashmap[k][i]
                return


fi = open("multimap.in")
fo = open("multimap.out", "w")

hashmap = [None] * 32469
for line in fi:
    data = line.split()

    if data[0] == "put":
        put(data[1], data[2])
    elif data[0] == "get":
        tmp = get(data[1])
    elif data[0] == "delete":
        delete(data[1], data[2])
    elif data[0] == "deleteall":
        deleteall(data[1])

fi.close()
fo.close()