X = 53
K = 274993
powX = []


def hash(p):
    h = 0
    m = len(p)
    for t in p:
        m -= 1
        h += (t * powX[m]) % K
        h %= K
    return h % K


# def buildH(s, m):
#     n = len(s)
#     h = [0 for _ in range(n-m+1)]
#     h[0] = hash(s[:m])
#     for i in range(n-m):
#         h[i+1] = (h[i]*X-s[i]*powX[m]+s[i+m]) % K
#     return h


c = 0
res = []


def Rabin_Karp(s, sub):
    global c, res
    m = len(sub)
    n = len(s)
    hsub = hash(sub)
    htmp = hash(s[:m])
    if htmp == hsub:
        c += 1
        res.append(0 + 1)
    for i in range(1, n - m + 1):
        htmp = ((htmp * X) % K - (s[i - 1] * (powX[m])) % K + s[i + m - 1]) % K
        if htmp != hsub:
            continue
        f = True

        for j in range(0, m, max(m//100, 1)):
            if s[i + j] != sub[j]:
                f = False
                break

        if f:
            c += 1
            res.append(i + 1)


def main():
    global powX
    fi = open("search2.in", "r")
    fo = open("search2.out", "w")

    bulavka = [ord(x) for x in list(fi.readline().strip())]
    seno = [ord(x) for x in list(fi.readline().strip())]
    m = len(bulavka)
    powX = [0 for _ in range(m + 1)]
    powX[0] = 1
    powX[1] = X
    for i in range(2, m + 1):
        powX[i] = (powX[i - 1] * X) % K

    Rabin_Karp(seno, bulavka)

    fo.write(str(c) + '\n')
    for x in res:
        fo.write(str(x) + " ")

    fi.close()
    fo.close()


if __name__ == '__main__':
    main()