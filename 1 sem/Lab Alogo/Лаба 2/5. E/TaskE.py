
def merge(left: list, right: list):
    result = []
    while (left != []) and (right != []):
        if left[0] <= right[0]:
            result.append(left[0])
            del left[0]
        else:
            result.append(right[0])
            del right[0]
    while left != []:
        result.append(left[0])
        del left[0]
    while right != []:
        result.append(right[0])
        del right[0]
    return result


def merge_sort(m: list):
    if len(m) <= 1:
        return m
    left = []
    right = []
    for i in range(len(m)):
        if i < (len(m) / 2):
            left.append(m[i])
        else:
            right.append(m[i])
    left = merge_sort(left)
    right = merge_sort(right)

    return merge(left, right)


fin = open("kth.in")
fout = open("kth.out", "w")

n, k = map(int, fin.readline().split())
a = [0]*n
A, B, C, a[0], a[1] = map(int, fin.readline().split())

j = 0
i = 2
while i < n:
    tmp = A*a[i-2] + B*a[i-1] + C
    a[i] = int.from_bytes((tmp & 0xFFFFFFFF).to_bytes(4, 'big'), 'big', signed=True)
    i += 1

a = merge_sort(a)

if a[k]:
    fout.write(str(a[k-1]))
else:
    fout.write(str(a[n-1]))

fin.close()
fout.close()