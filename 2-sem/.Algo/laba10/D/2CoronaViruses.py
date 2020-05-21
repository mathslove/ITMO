class Edge:
    def __init__(self, to_, w_):
        self.to = to_
        self.weight = w_


def check(v, graph, n):
    used = [False for x in range(n)]
    used = dfs(v, used, graph)
    for x in used:
        if not x:
            return False
    return True


def dfs(v, used, graph):
    st = [v]
    while st:
        s = st.pop()
        used[s] = True
        for u in graph[s]:
            if not used[u.to]:
                st.append(u.to)
    return used


class Comp:
    def __init__(self, amount, n):
        self.components = [0 for _ in range(amount)]
        self.num_of_comp = n


def DFS_straight(v, edges, used):
    for u in edges[v]:
        if not used[u.to]:
            used[u.to] = True
            used = DFS_straight(u.to, edges, used)
    topsort.append(v)
    return used


def DFS_reverse(v, rev_edges, components, ccount):
    components[v] = ccount
    for u in rev_edges[v]:
        if components[u.to] == 0:
            components = DFS_reverse(u.to, rev_edges, components, ccount)
    return components


topsort = []
def Cond(edges, n):
    global topsort
    used = [False for _ in range(n)]
    c = Comp(n, 0)
    for i in range(n):
        if not used[i]:
            used = DFS_straight(i, edges, used)

    reverse = [[] for _ in range(n)]
    for v in range(n):
        for u in edges[v]:
            reverse[u.to].append(Edge(v, u.weight))

    topsort.reverse()
    for u in topsort:
        if c.components[u] == 0:
            c.num_of_comp += 1
            c.components = DFS_reverse(u, reverse, c.components, c.num_of_comp)

    topsort = []
    return c


def chinese(edges, n, root):
    mst = 0
    if not check(root, edges, n):
        return -1

    minEdges = [9223372036854775807 for _ in range(n)]
    for v in range(n):
        for u in edges[v]:
            if u.weight < minEdges[u.to]:
                minEdges[u.to] = u.weight

    for v in range(n):
        if v != root:
            mst += minEdges[v]

    nullEdges = [[] for _ in range(n)]
    for v in range(n):
        for u in edges[v]:
            if u.weight == minEdges[u.to]:
                nullEdges[v].append(Edge(u.to, 0))

    if check(root, nullEdges, n):
        return mst

    c = Cond(nullEdges, n)
    newE = [[] for _ in range(c.num_of_comp)]

    for v in range(n):
        for u in edges[v]:
            if c.components[v] != c.components[u.to]:
                newE[c.components[v]].append(Edge(c.components[u.to], u.weight - minEdges[u.to]))

    mst += chinese(newE, c.num_of_comp, c.components[root])
    return mst


fi = open("chinese.in", "r")
fo = open("chinese.out", "w")

n, m = [int(x) for x in fi.readline().split()]

gout = [[] for _ in range(n)]

for i in range(m):
    b, e, w = [int(x) for x in fi.readline().split()]
    b -= 1
    e -= 1
    gout[b].append(Edge(e, w))

mst = chinese(gout, n, 0)

if mst != -1:
    print("yes".upper(), file=fo)
    print(mst, file=fo)
else:
    print("no".upper(), file=fo)

fi.close()
fo.close()

