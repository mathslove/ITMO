def heap_detector(arr: list):
    n = len(arr)
    for i in range(n // 2):
        if arr[2 * i + 1] < arr[i]:
            return False
        if (2 * i + 2 < n) and (arr[2 * i + 2] < arr[i]):
            return False

    return True


fin = open("isheap.in")
fout = open("isheap.out", "w")
n = int(fin.readline())
data = [int(x) for x in fin.readline().split()]

if heap_detector(data):
    fout.write("YES")
    print("yes")
else:
    print("no")
    fout.write("NO")

fin.close()
fout.close()