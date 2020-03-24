class Graph:
    def __init__(self, v):
        self.graph = [[] for _ in range(v)]

    def addEdge(self, u, v):
        self.graph[u].append(v)
        self.graph[v].append(u)

    def BFS(self, s):
        dist = [-1 for _ in range(v)]

        visited = [False] * (len(self.graph))

        dist[s] = 0

        queue = [s]

        visited[s] = True

        while queue:
            s = queue.pop(0)

            for i in (self.graph[s]):
                if visited[i] == False:
                    queue.append(i)
                    dist[i] = dist[s] + 1
                    visited[i] = True
        return dist


fi = open("pathbge1.in", "r")
fo = open("pathbge1.out", "w")

v, e = [int(x) for x in fi.readline().split()]

g = Graph(v)

for line in fi:
    b, e = [int(x) for x in line.split()]
    g.addEdge(b - 1, e - 1)

res = g.BFS(0)
for s in res:
    fo.write(str(s) + " ")

fi.close()
fo.close()