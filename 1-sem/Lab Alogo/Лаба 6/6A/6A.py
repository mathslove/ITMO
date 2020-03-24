def main():
    fi = open("height.in ")
    fo = open("height.out", "w")

    n = int(fi.readline())
    if n == 0:
        print(0, file=fo)
        return
    data = [None]
    for line in fi:
        tmp = [int(x) for x in line.split()]
        data.append(tmp)

    hi = [-1 for x in range(n+1)]
    hi[1] = 1
    i = 1
    while i<=n:
        l = data[i][1]
        r = data[i][2]
        if l != 0:
            hi[l] = hi[i] + 1
        if r != 0:
            hi[r] = hi[i] + 1
        i+=1

    print(max(hi), file=fo)

    fi.close()
    fo.close()
main()