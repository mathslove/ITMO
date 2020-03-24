def dfs(v :int):
    global c_num, used, comp, graph
    s = [v]
    while s:
        v = s.pop()
        used[v] = True
        comp[v] = c_num
        for u in graph[v]:
            if not used[u]:
                s.append(u)


fi = open("components.in", "r")
fo = open("components.out", "w")

v, e = fi.readline().split()
v = int(v)

graph = [[] for _ in range(v)]

for line in fi:
    tmp = [int(x) for x in line.split()]
    b, e = tmp[0]-1, tmp[1]-1
    graph[b].append(e)
    graph[e].append(b)

used = [False for _ in range(v)]
comp = [None for _ in range(v)]
c_num = 1
for i in range(v):
    if not used[i]:
        dfs(i)
        c_num += 1

print(c_num-1, file=fo)
for x in comp:
    fo.write(str(x) + " ")

fi.close()
fo.close()
