fi = open("bipartite.in", "r")
fo = open("bipartite.out", "w")

n, m = [int(x) for x in fi.readline().split()]

graph = [[] for _ in range(n)]
part = [0 for _ in range(n)]
f = True

for i in range(m):
    b, e = [int(x) for x in fi.readline().split()]
    graph[b - 1].append(e - 1)
    graph[e - 1].append(b - 1)

for i in range(n):
    if  part[i] == 0:
        part[i] = -1
        q = [i]
        while q:
            v = q.pop(0)
            for u in graph[v]:
                if part[u] == 0:
                    part[u] = -part[v]
                    q.append(u)
                elif part[u] == part[v]:
                    f = False
                    break


if f:
    print("YES", file=fo)
else:
    print("NO", file=fo)

fi.close()
fo.close()