def count_sort_mod(arr, index):
    main = [''] * len(arr)
    alphabet = [0] * 26

    for el in arr:
        alphabet[ord(el[index - 1]) % 97] += 1

    for i in range(1, len(alphabet)):
        alphabet[i] += alphabet[i - 1]

    for j in range(len(arr), 0, -1):
        main[alphabet[ord(arr[j - 1][index - 1]) % 97] - 1] = arr[j - 1]
        alphabet[ord(arr[j - 1][index - 1]) % 97] -= 1

    return main


def radix_sort(arr, m, k):
    for i in range(m, m - k, -1):
        arr = count_sort_mod(arr, i)
    return arr


with open("radixsort.in", 'r') as fi:
    n, m, k = [int(el) for el in fi.readline().split(" ", 2)]
    array = []
    for i in range(n):
        el = fi.readline().replace('\r', '').replace('\n', '')
        array.append(el)
    result = radix_sort(array, m, k)
    with open("radixsort.out", 'w') as fo:
        for el in result:
            fo.write(el + '\n')
