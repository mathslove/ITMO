f0 = open("turtle.in")
f1 = open("turtle.out", 'w')

def max(x,y):
    if x>y:
        return x
    else:
        return y

mas = []

h, w = map(int, f0.readline().split())

for y in range(h):
    mas.append([])
    mas[y].extend(map(int, f0.readline().split()))

print(mas)
print(w,h)

for y in range(h-1, -1, -1):
    for x in range(w):
        if x == 0:
            cell_left = 0;
        else:
            cell_left = mas[y][x-1]
        if y == (h-1):
            cell_down = 0
        else:
            cell_down = mas[y+1][x]
        print(y,' ',x)
        mas[y][x] += max(cell_down, cell_left)

f1.write(str(mas[0][w-1]))

f0.close()
f1.close()