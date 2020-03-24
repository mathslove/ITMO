class ListEl:
    def __init__(self, x):
        self.next = None
        self.val = x
        self.order = 0


class PriorityLine:
    def __init__(self):
        self.head = None
        self.tail = None

    def push(self, x):
        global k  # ВНИМАНИЕ ГЛОБАЛЬНАЯ ПЕРЕМЕННАЯ
        new = ListEl(x)
        if self.head is None:
            self.head = new
            self.tail = self.head
            self.tail.order = k
        else:
            self.tail.next = new
            self.tail.next.order = k
            self.tail = self.tail.next

    def extract_min(self):
        if self.head is None:
            return "*"

        if self.head == self.tail:
            min = self.head
            self.head = self.tail = None
        elif self.head.next == self.tail:
            if self.head.val <= self.tail.val:
                min = self.head
                self.head = self.tail
            else:
                min = self.tail
                self.tail = self.head
        else:
            min = self.head
            x = self.head
            prev = None
            while x.next is not None:
                if x.next.val < min.val:
                    min = x.next
                    prev = x
                x = x.next
            if min.next is None:
               prev.next = None
               self.tail = prev
            elif prev is None:
                self.head = min.next
            else:
                prev.next = min.next
        return min.val

    def decrease_key(self, x, y):
        key = self.head
        while key.order != x:
            key = key.next
        key.val = y


fi = open("priorityqueue.in")
fo = open("priorityqueue.out", "w")

pline = PriorityLine()
k = 0
while True:
    tmp = fi.readline().split()
    k += 1
    if len(tmp) == 0:
        break
    elif tmp[0] == "push":
        x = int(tmp[1])
        pline.push(x)
    elif tmp[0] == "extract-min":
        fo.write(str(pline.extract_min()) + "\n")
    elif tmp[0] == "decrease-key":
        x = int(tmp[1])
        y = int(tmp[2])
        pline.decrease_key(x, y)

fi.close()
fo.close()
