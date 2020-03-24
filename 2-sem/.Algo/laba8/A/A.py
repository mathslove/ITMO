fi = open("input.txt", "r")
fo = open("output.txt", "w")

v, e = fi.readline().split()
v = int(v)

matrix = [[] for _ in range(v)]
for i in range(v):
    matrix[i].extend([0 for _ in range(v)])

for line in fi:
    s, f = line.split()
    s = int(s) - 1
    f = int(f) - 1
    matrix[s][f] = 1

for row in matrix:
    print(' '.join(str(col) for col in row), file=fo)

fi.close()
fo.close()
