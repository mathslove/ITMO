fi = open("input.txt", "r")
fo = open("output.txt", "w")

n, m = [int(x) for x in fi.readline().split()]

graph = [[] for _ in range(n)]

for line in fi:
    b, e = [int(x) for x in line.split()]
    graph[b-1].append(e-1)
    graph[e-1].append(b-1)

for i in range(n):
    fo.write(str(len(graph[i])) + " ")

fi.close()
fo.close()