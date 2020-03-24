def bin_search(a: list, key: int):
    l = -1
    r = len(a)
    while l < r - 1:
        mid = (l + r) // 2
        if a[mid] < key:
            l = mid
        else:
            r = mid
    if r >= len(a):
        r = -2
    else:
        if a[r] != key:
            r = -2

    return r + 1


def bin_search_last(a: list, key: int):
    l = -1
    r = len(a)
    while l < r - 1:
        mid = (l + r) // 2
        if a[mid] > key:
            r = mid
        else:
            l = mid
    if a[l] != key:
        l = -2
    return l + 1


def first_last_index(data: list, req: list):
    return bin_search(data, req), bin_search_last(data, req)


def answer_printer(data: list, req: list):
    for i in range(len(req)):
        a, b = first_last_index(data, req[i])
        fout.write("{} {}\n".format(a, b))


fin = open("binsearch.in", "r")
fout = open("binsearch.out", "w")
n = int(fin.readline())
data = [int(x) for x in fin.readline().split()]
m = int(fin.readline())
req = [int(x) for x in fin.readline().split()]

answer_printer(data, req)

fin.close()
fout.close()