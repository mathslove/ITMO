def topsort(g):
    color = ["white" for _ in range(n)]
    cycle = False
    res = []
    stack = []
    for s in range(n):
        if color[s] != "black" and not cycle:
            stack.append([s, 1])
            while stack:
                v, dir = stack[-1]
                if dir == 1:
                    color[v] = "grey"
                    for u in g[v]:
                        if color[u] == "white":
                            stack.append([u, 1])
                            break
                        elif color[u] == "grey":
                            cycle = True
                            return None, cycle
                    stack[-1][1] = 0
                else:
                    color[v] = "black"
                    res.append(v)
                    stack.pop()

    return res.reverse(), cycle


fi = open("topsort.in", "r")
fo = open("topsort.out", "w")

n, m = fi.readline().split()
n = int(n)
m = int(m)

graph = [[] for _ in range(n)]

for line in fi:
    b, e = [int(x) for x in line.split()]
    graph[b - 1].append(e - 1)


ans, f = topsort(graph)

if not f:
    for x in ans:
        fo.write("{} ".format(x))
else:
    fo.write("-1")

fi.close()
fo.close()