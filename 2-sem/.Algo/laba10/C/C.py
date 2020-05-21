def get_root(v):
    if v == root[v]:
        return v
    root[v] = get_root(root[v])
    return root[v]


def U(a, b):
    a = get_root(a)
    b = get_root(b)
    if a != b:
        root[b] = a


fi = open("spantree3.in", "r")
fo = open("spantree3.out", "w")

n, m = [int(x) for x in fi.readline().split()]

g = []

for i in range(m):
    b, e, w = [int(x) for x in fi.readline().split()]
    g.append([w, [b-1, e-1]])
g.sort()

root = [x for x in range(n)]
res = 0

for i in range(m):
    w = g[i][0]
    b = g[i][1][0]
    e = g[i][1][1]
    if get_root(b) != get_root(e):
        res += w
        U(b, e)

print(res, file=fo)

fi.close()
fo.close()
