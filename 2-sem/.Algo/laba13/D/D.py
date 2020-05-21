import sys


def main():
    power = int(sys.stdin.readline().strip())
    s = sys.stdin.readline().strip()
    s += "#"
    n = len(s)
    res = [[0 for _ in range(power)] for _ in range(n)]
    pref = [0 for _ in range(n)]

    for i in range(1, n):
        j = pref[i - 1]
        while j > 0 and s[i] != s[j]:
            j = pref[j - 1]
        if s[i] == s[j]:
            j += 1
        pref[i] = j

    alphabet = [chr(i) for i in range(97, power+98)]
    for i in range(n):
        for c in range(power):
            if i > 0 and alphabet[c] != s[i]:
                res[i][c] = res[pref[i - 1]][c]
            else:
                if alphabet[c] == s[i]:
                    res[i][c] = i + 1

    for row in res:
        for cell in row:
            sys.stdout.write("{} ".format(cell))
        sys.stdout.write("\n")


if __name__ == '__main__':
    main()