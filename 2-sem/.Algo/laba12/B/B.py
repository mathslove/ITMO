# def Ford_Fulkerson(s, t):
#     par = [0 for _ in range(len(g))]
#
#     max_f = 0
#
#     def bfs(ss, tt):
#         visited = [False for _ in range(len(g))]
#         q = [ss]
#         visited[ss] = True
#
#         while q:
#             v = q.pop()
#
#             for u in range(len(g)):
#                 if not visited[u] and g[v][u] == 1:
#                     q.append(u)
#                     visited[u] = True
#                     par[u] = v
#
#         return visited[tt]
#
#     while bfs(s, t):
#         to = t
#         tmp = 0
#         while to != s:
#             frm = par[to]
#             g[frm][to] = 0
#             g[to][frm] = 1
#             tmp = to
#             to = par[to]
#
#         g[par[t]][t] = 0
#         g[s][tmp] = 0
#
#         max_f += 1
#
#     return max_f
#


def kuhn(frm):
    if visited[frm]:
        return False
    visited[frm] = True
    for i in range(len(g[frm])):
        to = g[frm][i]
        if matching[to] == -1 or kuhn(matching[to]):
            matching[to] = frm
            return True
    return False


fi = open("matching.in", "r")
fo = open("matching.out", "w")

n, m, k = [int(x) for x in fi.readline().split()]

# g = [[0 for __ in range(n + m + 2)] for _ in range(n + m + 2)]
#
# for i in range(k):
#     st, fn = [int(x) for x in fi.readline().split()]
#     g[st][fn + n] = 1
#
# for i in range(n):
#     g[0][i] = 1
#
# for i in range(m):
#     g[i][n + m + 1] = 1

g = [[] for _ in range(n)]
matching = [-1 for _ in range(m)]
used = [False for _ in range(n)]
visited = [False for _ in range(n)]

for i in range(k):
    t1, t2 = [int(x) for x in fi.readline().split()]
    g[t1 - 1].append(t2 - 1)

fi.close()

for i in range(n):
    for j in range(len(g[i])):
        if matching[g[i][j]] == -1:
            matching[g[i][j]] = i
            used[i] = True
            break

for i in range(n):
    if used[i]:
        continue
    for j in range(n):
        visited[j] = False
    kuhn(i)

value = 0
for i in range(m):
    if matching[i] != -1:
        value += 1

print(value, file=fo)

# print(Ford_Fulkerson(0, n + m + 1), file=fo)

fo.close()
