class node:
    def __init__(self, x):
        self.k = x
        self.l = None
        self.r = None
        self.p = None
        self.h = 1


class tree:
    def __init__(self):
        self.root = None

    def insert(self, x):
        if self.root is None:
            self.root = node(x)

        tmp = self.root
        while tmp:
            if x<tmp.k:
                if tmp.l:
                    tmp = tmp.l
                else:
                    tmp.l = node(x)
                    tmp.l.p = tmp
                    return
            elif x>tmp.k:
                if tmp.r:
                    tmp = tmp.r
                else:
                    tmp.r = node(x)
                    tmp.r.p = tmp
                    return
            else:
                return
        return

    def height_set(self, x):
        tmp = self.root
        while tmp:
            if x<tmp.k:
                tmp = tmp.l
            elif x>tmp.k:
                tmp = tmp.r
            else:
                break

        while tmp.p:
            if tmp.p.h <= tmp.h:
                tmp.p.h = tmp.h + 1
            tmp = tmp.p

    def rotateleft(self,el):
        tmp = el.r
        el.r = tmp.l
        tmp.l = el
        if self.hi(el.r) > self.hi(el.l):
            el.h = self.hi(el.r) + 1
        else:
            el.h = self.hi(el.l) + 1
        if self.hi(tmp.r) > self.hi(tmp.l):
            tmp.h = self.hi(tmp.r) + 1
        else:
            tmp.h = self.hi(tmp.l) + 1
        self.root = tmp

    def rotateright(self, el):
        tmp = el.l
        el.l = tmp.r
        tmp.r = el
        if self.hi(el.r) > self.hi(el.l):
            el.h = self.hi(el.r) + 1
        else:
            el.h = self.hi(el.l) + 1
        if self.hi(tmp.r) > self.hi(tmp.l):
            tmp.h = self.hi(tmp.r) + 1
        else:
            tmp.h = self.hi(tmp.l) + 1

        self.root.r = tmp

    def hi(self, el):
        if el:
            return el.h
        else:
            return 0

    def bal(self, el):
        return self.hi(el.r) - self.hi(el.l)

    def balance(self):
        if self.hi(self.root.r) > self.hi(self.root.l):
            self.root.h = self.hi(self.root.r) + 1
        else:
            self.root.h = self.hi(self.root.l) + 1

        if self.bal(self.root) >= 2:
            if self.bal(self.root.r) < 0:
                self.rotateright(self.root.r)
            self.rotateleft(self.root)
            return


def output(el):
    if el is None:
        return

    out.append(el.k)

    if el.l:
        lo[el.k] = len(out) + 1
    else:
        lo[el.k] = 0

    output(el.l)

    if el.r:
        ro[el.k] = len(out) + 1
    else:
        ro[el.k] = 0

    output(el.r)


fi = open("rotation.in")
fo = open("rotation.out", "w")

n = int(fi.readline())
data = [None for _ in range(n+1)]
left = [None for _ in range(n + 1)]
right = [None for _ in range(n + 1)]
i = 1
for line in fi:
    tmp = [int(_) for _ in line.split()]
    data[i] = tmp[0]
    left[i] = tmp[1]
    right[i] = tmp[2]
    i+=1

T = tree()
T.root = node(data[1])
for i in range(1,n+1):
    if left[i]:
        T.insert(data[left[i]])
    if right[i]:
        T.insert(data[right[i]])
    if left[i]+right[i] == 0:
        T.height_set(data[i])

out = []
lo = {}
ro = {}
T.balance()
output(T.root)
print(len(out), file=fo)
for i in range(1, n+1):
    print(out[i-1], lo[out[i-1]], ro[out[i-1]], file=fo)

fi.close()
fo.close()
