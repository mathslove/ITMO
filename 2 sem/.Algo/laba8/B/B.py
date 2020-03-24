fi = open("input.txt", "r")
fo = open("output.txt", "w")

v = int(fi.readline())

matrix = [[] for _ in range(v)]
for i in range(v):
    matrix[i].extend([0 for _ in range(v)])


for i in range(v):
    line = fi.readline().split()
    for j in range(v):
        matrix[i][j] = int(line[j])

f = False
for i in range(v):
    for j in range(i, v):
        if matrix[i][j] != matrix[j][i] or (i == j and matrix[i][j] == 1):
            f = True


if f:
    print("NO", file=fo)
else:
    print("YES", file=fo)

fi.close()
fo.close()
