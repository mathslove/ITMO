fi = open("in.txt")
fo = open("out.txt", "w")
out = open("check.txt", "w")

a = []
for line in fi:
    tmp = line.split()
    x = int(tmp[1])
    if tmp[0] == "+":
        a.append(x)
        a.sort()
    elif tmp[0] == "-":
        if x in a:
            a.remove(x)
            a.sort()
    elif tmp[0] == ">":
        flag = False
        if x in a:
            res = a.index(x)
        else:
            for el in a:
                if el > x:
                    f = a.index(el)
                    res = len(a) + 1-f
                    flag = True
                    break
        if flag:
            print(res, file=fo)
        else:
            print(len(a), file=fo)
        # if not(len(a)-f) == int(fo.readline()):
        #     print(line, file=out)
    elif tmp[0] == "<":
        flag = False
        if x in a:
            res = a.index(x)
        else:
            for el in a:
                if el > x:
                    f = a.index(el)
                    res = f
                    flag = True
                    break
        if flag:
            print(res, file=fo)
        else:
            print(len(a), file=fo)

        # if not ((f) == int(fo.readline())):
        #     print(line, file=out)

fi.close()
fo.close()
out.close()