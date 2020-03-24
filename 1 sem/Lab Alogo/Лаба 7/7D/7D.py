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

    def hi(self, el):
        return el.h if el else 0

    def bal(self, el):
        return self.hi(el.r) - self.hi(el.l)

    def rotate_right(self, el):
        tmp = el.l
        el.l = tmp.r
        tmp.r = el
        el.h = self.hi(el.r) if self.hi(el.r) > self.hi(el.l) else self.hi(el.l)
        el.h += 1
        tmp.h = self.hi(tmp.r) if self.hi(tmp.r) > self.hi(tmp.l) else self.hi(tmp.l)
        tmp.h += 1
        return tmp

    def rotate_left(self, el):
        tmp = el.r
        el.r = tmp.l
        tmp.l = el
        el.h = self.hi(el.r) if self.hi(el.r) > self.hi(el.l) else self.hi(el.l)
        el.h += 1
        tmp.h = self.hi(tmp.r) if self.hi(tmp.r) > self.hi(tmp.l) else self.hi(tmp.l)
        tmp.h += 1
        return tmp

    def balance(self, el):
        el.h = self.hi(el.r) if self.hi(el.r) > self.hi(el.l) else self.hi(el.l)
        el.h += 1
        if self.bal(el) == 2:
            if self.bal(el.r) < 0:
                el.r = self.rotate_right(el.r)
            return self.rotate_left(el)
        if self.bal(el) == -2:
            if self.bal(el.l) > 0:
                el.l = self.rotate_left(el.l)
            return self.rotate_right(el)

        return el

    def insert(self,el, x):
        if not el:
            return node(x)
        if x < el.k:
            el.l = self.insert(el.l, x)
        else:
            el.r = self.insert(el.r, x)
        return self.balance(el)

    def draw(self, el, x):
        if el is None:
            return node(x)

        if x < el.k:
            el.l = self.draw(el.l, x)
        else:
            el.r = self.draw(el.r, x)
        el.h = self.hi(el.r) if self.hi(el.r) > self.hi(el.l) else self.hi(el.l)
        el.h += 1
        return el

    def find_max(self, el):
        return self.find_max(el) if el.r else el

    def remove_max(self, el):
        if el.r is None:
            return el.l

        el.r = self.remove_max(el.r)
        return self.balance(el)

    def remove(self, el, k):
        if el is None:
            return 0

        if k < el.k:
            el.l = self.remove(el.l, k)
        elif k > el.k:
            el.r = self.remove(el.r, k)
        else:
            el_l = el.l
            el_r = el.r
            del el
            if el_l is None:
                return el_r
            m = self.find_max(el_l)
            m.l = self.remove_max(el_l)
            m.r = el_r
            return self.balance(m)
        return self.balance(el)


out = []
lo = {}
ro = {}


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


fi = open("deletion.in")
fo = open("deletion.out", "w")

n = int(fi.readline())
data = [None for _ in range(n+1)]
left = [None for _ in range(n+1)]
right = [None for _ in range(n+1)]

for i in range(1, n+1):
    k, l, r = map(int, fi.readline().split())
    data[i] = k
    left[i] = l
    right[i] = r

T = tree()
root = node(data[1])
for i in range(1, n+1):
    if left[i] != 0:
        root = T.draw(root, data[left[i]])
    if right[i] != 0:
        root = T.draw(root, data[right[i]])

k = int(fi.readline())
n -= 1
root = T.remove(root, k)

output(root)
print(len(out), file=fo)
for i in range(1, n+1):
    print(out[i-1], lo[out[i-1]], ro[out[i-1]], file=fo)

fi.close()
fo.close()
