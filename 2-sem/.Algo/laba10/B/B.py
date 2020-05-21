def dist(x0, y0, x1, y1):
    return (x1-x0)**2+(y1-y0)**2


fi = open("spantree.in","r")
fo = open("spantree.out", "w")

n = [int(x) for x in fi.readline().split()][0]

g = [[None, None] for _ in range(n)]
d = [0 for _ in range(n)]
tree = [False for _ in range(n)]
tree[0] = True
mst = 0
for i in range(n):
    x, y = [int(_) for _ in fi.readline().split()]
    g[i][0] = x
    g[i][1] = y
    d[i] = dist(g[0][0], g[0][1], x, y)

for i in range(1, n):
    min = 10000000000
    m = 0
    for j in range(1, n):
        if d[j] < min and not tree[j]:
            min = d[j]
            m = j
    mst += min**(1/2)
    tree[m] = True
    for z in range(1, n):
        if not tree[z]:
            tmp = dist(g[m][0], g[m][1], g[z][0], g[z][1])
            if tmp < d[z]:
                d[z] = tmp

print(mst)

fi.close()
fo.close()