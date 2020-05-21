def new_f(v, e, f):
    if v == e:
        return f
    u[v] = True
    for vv in range(n):
        if not u[vv] and g[v][vv] > 0:
            ff = new_f(vv, e, min(f, g[v][vv]))
            if ff > 0:
                g[v][vv] -= ff
                g[vv][v] += ff
                return ff
    return 0


fi = open("maxflow.in", "r")
fo = open("maxflow.out", "w")

n, m = [int(x) for x in fi.readline().split()]

g = [[0 for __ in range(n)] for _ in range(n)]

for i in range(m):
    s, fn, w = [int(x) for x in fi.readline().split()]
    g[s-1][fn-1] = w

fi.close()

max_f = 0
u = [False for _ in range(n)]
added_f = 1
while added_f>0:
    u = [False for _ in u]
    added_f = new_f(0, n-1, float("inf"))
    max_f += added_f

print(max_f, file=fo)
fo.close()
