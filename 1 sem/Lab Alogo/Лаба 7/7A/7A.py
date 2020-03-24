def main():
    fi = open("balance.in")
    fo = open("balance.out", "w")

    n = int(fi.readline())

    par = [0 for x in range(n+1)]
    pos = [0 for x in range(n+1)]
    hi_r = [0 for x in range(n+1)]
    hi_l = [0 for x in range(n+1)]
    data = [None]

    for line in fi:
        tmp = [int(x) for x in line.split()]
        data.append(tmp)

    for i in range(1, n+1):
        pos[data[i][1]] = -1
        pos[data[i][2]] = 1
        par[data[i][1]] = par[data[i][2]] = i

    for i in range(n, 0, -1):
        if pos[i] == 1:
            hi_r[par[i]] += max(hi_l[i], hi_r[i]) + 1
        if pos[i] == -1:
            hi_l[par[i]] += max(hi_l[i], hi_r[i]) + 1

    for i in range(1, n+1):
        b = hi_r[i] - hi_l[i]
        print(b, file=fo)

    fi.close()
    fo.close()


main()