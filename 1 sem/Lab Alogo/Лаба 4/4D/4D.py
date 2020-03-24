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


fi = open("postfix.in")
fo = open("postfix.out", "w")

tmp = list(fi.readline().split())
stack = Stack()
for x in tmp:
    if x == "+":
        b = int(stack.pop())
        a = int(stack.pop())
        stack.push(a+b)
    elif x == "-":
        b = int(stack.pop())
        a = int(stack.pop())
        stack.push(a - b)
    elif x == "*":
        b = int(stack.pop())
        a = int(stack.pop())
        stack.push(a * b)
    else:
        stack.push(x)

fo.write(str(stack.pop()))

fi.close()
fo.close()
