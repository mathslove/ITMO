def func():
    # global maze, s_x, s_y, f_x, f_y
    q = [[s_y, s_x]]
    while q and maze[f_y][f_x] == 0:
        tmp = q.pop(0)
        if tmp[0] < m - 1 and maze[tmp[0] + 1][tmp[1]] == 0:
            maze[tmp[0] + 1][tmp[1]] = maze[tmp[0]][tmp[1]] + 1
            q.append([tmp[0] + 1, tmp[1]])
        if tmp[0] > 0 and maze[tmp[0] - 1][tmp[1]] == 0:
            maze[tmp[0] - 1][tmp[1]] = maze[tmp[0]][tmp[1]] + 1
            q.append([tmp[0] - 1, tmp[1]])
        if tmp[1] < n - 1 and maze[tmp[0]][tmp[1] + 1] == 0:
            maze[tmp[0]][tmp[1]+1] = maze[tmp[0]][tmp[1]] + 1
            q.append([tmp[0], tmp[1]+1])
        if tmp[1] > 0 and maze[tmp[0]][tmp[1] - 1] == 0:
            maze[tmp[0]][tmp[1]-1] = maze[tmp[0]][tmp[1]] + 1
            q.append([tmp[0], tmp[1] - 1])


fi = open("input.txt", "r")
fo = open("output.txt", "w")

m, n = [int(x) for x in fi.readline().split()]

maze = [[None for _ in range(n)] for x in range(m)]

i = 0
for line in fi:
    maze[i] = [x for x in line]
    if "\n" == maze[i][len(maze[i])-1]:
        maze[i].pop()
    j = 0
    for j in range(n):
        if maze[i][j] == ".":
            maze[i][j] = 0
        elif maze[i][j] == "#":
            maze[i][j] = -1
        elif maze[i][j] == "S":
            maze[i][j] = 1
            s_x = j
            s_y = i
        elif maze[i][j] == "T":
            maze[i][j] = 0
            f_x = j
            f_y = i
    i += 1

func()

print(maze[f_y][f_x]-1, file=fo)

if maze[f_y][f_x] != 0:
    res = []
    i = f_y
    j = f_x
    while i != s_y or j != s_x:
        if i < m - 1 and maze[i + 1][j] == maze[i][j] - 1:
            i+=1
            res.append("U")
        if i > 0 and maze[i - 1][j] == maze[i][j] - 1:
            i-=1
            res.append("D")
        if j < n - 1 and maze[i][j+1] == maze[i][j] - 1:
            j+=1
            res.append("L")
        if j > 0 and maze[i][j-1] == maze[i][j] - 1:
            j-=1
            res.append("R")
    res.reverse()
    for x in res:
        fo.write(str(x) + " ")


fi.close()
fo.close()