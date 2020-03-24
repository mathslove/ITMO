def main():
    fi = open("check.in ")
    fo = open("check.out", "w")

    n = int(fi.readline())
    if n == 0:
        print("yes".upper(), file=fo)
        return

    max = [None for x in range(n + 1)]
    min = [None for x in range(n + 1)]
    max[1] = 10 ** 9 + 1
    min[1] = -10 ** 9 - 1
    flag = True

    data = [None]
    i = 1
    for line in fi:
        tmp = [int(x) for x in line.split()]
        data.append(tmp)
        k = data[i][0]
        l = data[i][1]
        r = data[i][2]
        min[l] = min[i]
        max[l] = k
        min[r] = k
        max[r] = max[i]
        if k <= min[i] or k >= max[i]:
            flag = False
            break
        i+=1

    if flag:
        print("yes".upper(), file=fo)
    else:
        print("no".upper(), file=fo)

    fi.close()
    fo.close()

main()