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
        if self.top == None:
            x = None
        else:
            x = self.top.val
            self.top = self.top.prev
        return x

fi = open("brackets.in")
fo = open("brackets.out", "w")


tmp = []
while True:
    tmp = list(fi.readline().strip())
    stack = Stack()
    k = 0
    if len(tmp) == 0:
        break
    for i in range(len(tmp)):
        if tmp[i] == "(" or tmp[i] == "[":
            stack.push(tmp[i])
        elif tmp[i] == ")":
            x = stack.pop()
            if x != "(":
                k = 1
                break
        elif tmp[i] == "]":
            x = stack.pop()
            if x != "[":
                k = 1
                break
        else:
            break
    if k == 0 and (stack.pop() is None):
        fo.write("YES"+"\n")
    else:
        fo.write("NO" + "\n")



fi.close()
fo.close()