def hamilton(curr):
    Path.append(curr)
    if len(Path) == n:
        if matrix[Path[0]][Path[-1]] == 1:
            return True
        else:
            Path.pop()
            return False
    Visited[curr] = True
    for next in range(n):
        if matrix[curr][next] == 1 and not Visited[next]:
            if hamilton(next):
                return True
    Visited[curr] = False
    Path.pop()
    return False

fi = open("hamiltonian.in", "r")
fo = open("hamiltonian.out", "w")

n, m = [int(x) for x in fi.readline().split()]

matrix = [[] for _ in range(n)]
for i in range(n):
    matrix[i].extend([0 for _ in range(n)])

for i in range(m):
    s, f = fi.readline().split()
    s = int(s) - 1
    f = int(f) - 1
    matrix[s][f] = 1

Visited = [False] * n
Path = []

if hamilton(0):
    fo.write("YES")
else:
    fo.write("NO")

fi.close()
fo.close()