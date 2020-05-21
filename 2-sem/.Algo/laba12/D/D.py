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
    def __init__(self, f, t, c, fl):
        self.frm = f
        self.to = t
        self.capacity = c
        self.flow = fl


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


def dfs(vertex=source, flow=float("inf")):
    if not flow:
        return 0

    if vertex == sink:
        return flow

    while ptr[vertex] < len(g[vertex]):
        edge = g[vertex][ptr[vertex]]
        if level[vertex] + 1 == level[edges[edge].to]:
            pushed = dfs(edges[edge].to, min(flow, edges[edge].capacity - edges[edge].flow))
            if pushed:
                edges[edge].flow += pushed
                check = edge ^ 1
                edges[edge ^ 1].flow -= pushed
                return pushed
        ptr[vertex] += 1

    return 0


def add(frm, to, capacity):
    g[frm].append(len(edges))
    edges.append(Edge(frm, to, capacity, 0))
    g[to].append(len(edges))
    edges.append(Edge(to, frm, 0, 0))


def main():
    global g, ptr, source, sink, n, m

    fi = open("circulation.in", "r")
    fo = open("circulation.out", "w")

    n, m = [int(x) for x in fi.readline().split()]
    n += 2

    g = [[] for _ in range(n)]
    ptr = [0 for _ in range(n)]
    sink = n - 1

    for i in range(m):
        frm, to, lf, hf = [int(x) for x in fi.readline().split()]
        add(source, to, lf)
        add(frm, to, hf - lf)
        add(frm, sink, lf)

    fi.close()

    while bfs():
        while dfs():
            pass
        ptr = [0 for _ in range(n)]

    for edge in g[0]:
        if edges[edge].flow < edges[edge].capacity:
            print("NO", file=fo)
            return

    print("YES", file=fo)
    for i in range(0, len(edges), 6):
        print(edges[i + 2].flow + edges[i + 4].flow, file=fo)

    fo.close()
    return


if __name__ == '__main__':
    main()
