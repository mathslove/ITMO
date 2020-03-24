class listel:
    def __init__(self, k, x1=None, x2=None):
        self.next = None
        self.prev = None
        self.k = k
        self.x1 = x1
        self.x2 = x2


class dlist:
    def __init__(self):
        self.tail = None
        self.head = None

    def lpush(self, k, x1, x2):
        new = listel(k, x1, x2)
        if self.head is None:
            self.head = new
            self.tail = new
        else:
            tmp = self.tail
            self.tail.next = new
            self.tail = new
            self.tail.prev = tmp
        return self.tail

    def lrepush(self, k, x1, x2):
        tmp = self.head
        while tmp:
            if k == tmp.k and x1 == tmp.x1:
                tmp.x2 = x2
                return tmp
            tmp = tmp.next

    def ldelete(self, k, x1):
        tmp = self.head
        while tmp:
            if tmp.k == k and tmp.x1 == x1:
                if tmp == self.head:
                    self.head = tmp.next
                if tmp == self.tail:
                    self.tail = tmp.prev
                if tmp.next:
                    tmp.next.prev = tmp.prev
                if tmp.prev:
                    tmp.prev.next = tmp.next
                return tmp
            tmp = tmp.next
        return None


def put(k, x1, x2):
    if hash_f[k] is not None:
        for i in range(len(hash_f[k])):
            if hash_f[k][i][0] == x1:
                hash_f[k][i][1] = x2
                link.lrepush(k, x1, x2)
                return
        pt = link.lpush(k, x1, x2)
        hash_f[k].append([x1, x2, pt])
        if pt.prev:
            for i in range(len(hash_f[pt.prev.k])):
                if hash_f[pt.prev.k][i][0] == x1:
                    hash_f[pt.prev.k][i][2] = pt.prev
                    break
    else:
        pt = link.lpush(k, x1, x2)
        hash_f[k] = []
        hash_f[k].append([x1, x2, pt])
        if pt.prev:
            for i in range(len(hash_f[pt.prev.k])):
                if hash_f[pt.prev.k][i][0] == x1:
                    hash_f[pt.prev.k][i][2] = pt.prev
                    break


def delete(k, x1):
    if hash_f[k] is not None:
        if len(hash_f[k]) == 0:
            hash_f[k] = None
            return
        pt = link.ldelete(k, x1)
        for i in range(len(hash_f[k])):
            if hash_f[k][i][0] == x1:
                hash_f[k][i], hash_f[k][len(hash_f[k]) - 1] = hash_f[k][len(hash_f[k]) - 1], hash_f[k][i]
                hash_f[k].pop()
                if pt.prev:
                    for i in range(len(hash_f[pt.prev.k])):
                        if hash_f[pt.prev.k][i][0] == x1:
                            hash_f[pt.prev.k][i][2] = pt.prev
                            break
                if pt.next:
                    for i in range(len(hash_f[pt.next.k])):
                        if hash_f[pt.next.k][i][0] == x1:
                            hash_f[pt.next.k][i][2] = pt.next
                            break
                break


def get(k, x1):
    if hash_f[k] is not None:
        for i in range(len(hash_f[k])):
            if hash_f[k][i][0] == x1:
                return hash_f[k][i][1]
    return "none"


def prev(k, x1):
    if hash_f[k] is not None:
        for i in range(len(hash_f[k])):
            if hash_f[k][i][0] == x1:
                if hash_f[k][i][2].prev:
                    return hash_f[k][i][2].prev.x2
                else:
                    return "none"
    return "none"


def next(k, x1):
    if hash_f[k] is not None:
        for i in range(len(hash_f[k])):
            if hash_f[k][i][0] == x1:
                if hash_f[k][i][2].next:
                    return hash_f[k][i][2].next.x2
                else:
                    return "none"
    return "none"


fi = open("linkedmap.in")
fo = open("linkedmap.out", "w")

P = 32
link = dlist()
hash_f = [None] * 1000000
data = []
for line in fi:
    data = line.split()

    k = 0
    i = 0
    for el in data[1]:
        k += (ord(el) % 97 + 1) * (P ** i)
        i += 1
    k %= 10 ** 6

    if data[0] == "put":
        put(k, data[1], data[2])
    elif data[0] == "delete":
        delete(k, data[1])
    elif data[0] == "get":
        print(get(k, data[1]), file=fo)
    elif data[0] == "prev":
        print(prev(k, data[1]), file=fo)
    elif data[0] == "next":
        print(next(k, data[1]), file=fo)

fi.close()
fo.close()