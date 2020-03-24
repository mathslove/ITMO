class Node:
    def __init__(self, k):
        self.k = k
        self.l = None
        self.r = None


class BST:
    def __init__(self):
        self.root = None

    def insert(self, x):
        if self.root is None:
            self.root = Node(x)
            return
        cur = self.root
        while cur:
            if x < cur.k:
                if cur.l is None:
                    cur.l = Node(x)
                else:
                    cur = cur.l
            elif x > cur.k:
                if cur.r is None:
                    cur.r = Node(x)
                else:
                    cur = cur.r
            else:
                return
        return

    def exists(self, x):
        tmp = self.root
        while tmp:
            if tmp.k > x:
                tmp = tmp.l
            elif tmp.k < x:
                tmp = tmp.r
            else:
                return True
        return False

    def next(self, x):
        tmp = self.root
        suc = None
        while tmp:
            if tmp.k > x:
                suc = tmp.k
                tmp = tmp.l
            else:
                tmp = tmp.r
        return suc

    def prev(self, x):
        tmp = self.root
        pre = None
        while tmp:
            if tmp.k < x:
                pre = tmp.k
                tmp = tmp.r
            else:
                tmp = tmp.l
        return pre

    def delete(self, x):
        cur = self.root
        parent = None
        flag = False
        while cur:
            if x < cur.k:
                parent = cur
                cur = cur.l
                flag = True
            elif x > cur.k:
                parent = cur
                cur = cur.r
                flag = False
            else:
                break

        if cur is None:
            return
        if cur.k != x:
            return
        if cur.l:
            tmp = cur.l
            while tmp.r:
                tmp = tmp.r
            tmp.r = cur.r
            cur = cur.l
        else:
            cur = cur.r
        if parent:
            if flag:
                parent.l = cur
            else:
                parent.r = cur
        else:
            self.root = cur


def main():
    fi = open("bstsimple.in")
    fo = open("bstsimple.out", "w")

    tree = BST()
    for line in fi:
        data = line.split()
        x = int(data[1])
        if data[0] == "insert":
            tree.insert(x)
        if data[0] == "exists":
            if tree.exists(x):
                print("true", file=fo)
            else:
                print("false", file=fo)
        if data[0] == "prev":
            tmp = tree.prev(x)
            if tmp:
                print(tmp, file=fo)
            else:
                print("none", file=fo)
        if data[0] == "next":
            tmp = tree.next(x)
            if tmp:
                print(tmp, file=fo)
            else:
                print("none", file=fo)
        if data[0] == "delete":
            tree.delete(x)

    fi.close()
    fo.close()


main()
