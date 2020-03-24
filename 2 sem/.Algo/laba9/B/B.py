def dfs(v):
    global cycle_start, cycle_end
    color[v] = "grey"
    for u in graph[v]:
        if color[u] == "white":
            parent[u] = v
            if dfs(u):
                return True
        elif color[u] == "grey":
            cycle_end = v
            cycle_start = u
            return True

    color[v] = "black"
    return False


fi = open("cycle.in", "r")
fo = open("cycle.out", "w")

n, m = fi.readline().split()
n = int(n)
m = int(m)

graph = [[] for _ in range(n)]
parent = [None for _ in range(n)]
color = ["white" for _ in range(n)]
cycle_start = -1

for line in fi:
    b, e = [int(x) for x in line.split()]
    graph[b - 1].append(e - 1)

for i in range(n):
    if dfs(i):
        break

if cycle_start == -1:
    print("no".capitalize(), file= fo)
else:
    print("yes".capitalize(), file=fo)
    cycle=[]
    v = cycle_end
    cycle.append(cycle_start)
    while v != cycle_start:
        cycle.append(v)
        v = parent[v]
    cycle.reverse()
    for x in cycle:
        fo.write("{} ".format(x+1))

fi.close()
fo.close()
