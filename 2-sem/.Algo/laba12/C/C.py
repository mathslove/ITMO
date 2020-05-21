g = []
ans = []
edges = []
ptr = []
level = []
source = 0
sink = 0
n = 0
m = 0


class Edge:
    def __init__(self, f, t, c, fl, n):
        self.frm = f
        self.to = t
        self.capacity = c
        self.flow = fl
        self.number = n


def bfs():
    global level
    level = [0 for _ in range(n)]
    q = [source]
    level[source] = 1
    while q and level[sink] == 0:
        v = q.pop(0)

        for edge in g[v]:
            if not level[edges[edge].to] and edges[edge].capacity > edges[edge].flow:
                q.append(edges[edge].to)
                level[edges[edge].to] = level[v] + 1

    return bool(level[sink])


def dfs(flow, vertex=source ):
    if not flow:
        return 0

    if vertex == sink:
        return flow

    while ptr[vertex] < len(g[vertex]):
        edge = g[vertex][ptr[vertex]]
        if level[vertex] + 1 == level[edges[edge].to]:
            pushed = dfs(edges[edge].capacity - edges[edge].flow if flow > (edges[edge].capacity - edges[edge].flow) else flow, edges[edge].to)
            if pushed:
                edges[edge].flow += pushed
                edges[edge ^ 1].flow -= pushed
                return pushed
        ptr[vertex] += 1

    return 0


def decomposition(vertex, minFlow=float("inf")):
    if vertex == sink:
        ans.append([])
        return minFlow

    for edge in g[vertex]:
        if edges[edge].flow > 0:
            result = decomposition(edges[edge].to, min(minFlow, edges[edge].flow))
            if result:
                ans[-1].append(edges[edge].number)
                if vertex == source:
                    ans[-1].append(len(ans[len(ans) - 1]))
                    ans[-1].append(result)
                    ans[-1].reverse()
                edges[edge].flow -= result
                return result
    return 0


def main():
    global g, ptr, source, sink, n, m, ans

    fi = open("decomposition.in", "r")
    fo = open("decomposition.out", "w")

    n, m = [int(x) for x in fi.readline().split()]

    g = [[] for _ in range(n)]
    ptr = [0 for _ in range(n)]
    sink = n - 1

    for i in range(m):
        frm, to, cp = [int(x) for x in fi.readline().split()]
        g[frm - 1].append(len(edges))
        edges.append(Edge(frm - 1, to - 1, cp, 0, i + 1))
        g[to - 1].append(len(edges))
        edges.append(Edge(to - 1, frm - 1, 0, 0, i + 1))

    fi.close()

    while bfs():
        while dfs(float("inf")): pass
        ptr = [0 for _ in range(n)]

    while decomposition(source): pass

    fo.write(str(len(ans)) + "\n")
    for aa in ans:
        for aaa in aa:
            fo.write(str(aaa) + " ")
        fo.write("\n")

    fo.close()
    return


if __name__ == '__main__':
    main()
