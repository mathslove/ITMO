def sift_down(arr: list, n: int, i: int):
    parent = i
    l = 2 * i + 1
    r = 2 * i + 2
    if l < n and arr[i] < arr[l]:
        parent = l
    if r < n and arr[parent] < arr[r]:
        parent = r
    if parent != i:
        arr[i], arr[parent] = arr[parent], arr[i]
        sift_down(arr, n, parent)


def heapSort(arr: list):
    n = len(arr)
    for i in range(n//2+1, -1, -1):
        sift_down(arr, n, i)
    for i in range(n - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        sift_down(arr, i, 0)


fin = open("sort.in")
fout = open("sort.out", "w")
n = int(fin.readline())
data = [int(x) for x in fin.readline().split()]

heapSort(data)
fout.write(" ".join(str(x) for x in data))

fin.close()
fout.close()
