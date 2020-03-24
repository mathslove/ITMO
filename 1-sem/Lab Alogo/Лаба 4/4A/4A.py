class ListElement:
    def __init__(self, x):
        self.prev = None
        self.val = x


class Stack:
    def __init__(self):
        self.top = None

    def push(self, x):
        new = ListElement(x)
        new.prev = self.top
        self.top = new

    def pop(self):
        x = self.top.val
        self.top = self.top.prev
        return x


fi = open("stack.in", "r")
fo = open("stack.out", "w")

n = int(fi.readline())

my_stack = Stack()
k = 0
tmp = []
for i in range(n):
    tmp = fi.readline().split()
    if tmp[0] == "+":
        tmp[1] = int(tmp[1])
        my_stack.push(tmp[1])
    if tmp[0] == "-":
        if k == 0:
            fo.write(str(my_stack.pop()))
        else:
            fo.write("\n" + str(my_stack.pop()))
        k+=1

fi.close()
fo.close()