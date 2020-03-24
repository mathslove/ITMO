class ListEl:
    def __init__(self, x):
        self.next = None
        self.val = x


class Line:
    def __init__(self):
        self.head = None
        self.tail = None

    def push(self, x):
        new = ListEl(x)
        if self.tail == None:
            self.head = new
        else:
            self.tail.next = new
        self.tail = new

    def pop(self):
        x = self.head.val
        self.head = self.head.next
        if self.head == None:
            self.tail = None
        return x


fi = open("queue.in", "r")
fo = open("queue.out", "w")

n = int(fi.readline())

MY_LINE = Line()
tmp = []
k = 0
for i in range(n):
    tmp = fi.readline().split()
    if tmp[0] == "+":
        tmp[1] = int(tmp[1])
        MY_LINE.push(tmp[1])
    if tmp[0] == "-":
        if k == 0:
            fo.write(str(MY_LINE.pop()))
        else:
            fo.write("\n" + str(MY_LINE.pop()))
        k += 1

fo.close()
fi.close()