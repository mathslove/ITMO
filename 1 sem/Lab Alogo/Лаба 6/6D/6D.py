class ListEl:
    def __init__(self, element):
        self.data = element
        self.next = None


class List:
    def __init__(self):
        self.head = None
        self.tail = None

    def enq(self, element):
        new = ListEl(element)
        if self.tail:
            self.head.next = new
        else:
            self.tail = new

        self.head = new

    def dequeue(self):
        result = self.tail.data
        self.tail = self.tail.next
        return result

    def enqueue(self, value):
        self.enq(int(value) % 0x10000)


class QuackInterpreter:
    def __init__(self, prog, fo):
        self.is_program_running = False
        self.prog = prog
        self.out = fo
        self.line = List()
        self.regs = [0] * 26
        self.current_command_in_prg = 0

    def mul(self):
        a = self.line.dequeue()
        b = self.line.dequeue()
        self.line.enqueue(a * b)
        self.current_command_in_prg += 1

    def start(self):
        self.is_program_running = True
        for step in range(100000):
            if self.is_program_running and len(self.prog) != self.current_command_in_prg:
                self.do_next()
            else:
                break

    def add(self):
        x = self.line.dequeue()
        y = self.line.dequeue()
        self.line.enqueue(x + y)
        self.current_command_in_prg += 1

    def sub(self):
        x = self.line.dequeue()
        y = self.line.dequeue()
        self.line.enqueue(x - y)
        self.current_command_in_prg += 1

    def jmp(self, label):
        # make normal jump to label??
        for i in range(len(self.prog)):
            if self.prog[i] == ":{}".format(label):
                self.current_command_in_prg = i
                return
        raise RuntimeError("Label not found: {}!".format(label))

    def div(self):
        x = self.line.dequeue()
        y = self.line.dequeue()
        if y != 0:
            self.line.enqueue(x // y)
        else:
            self.line.enqueue(0)
        self.current_command_in_prg += 1

    def mod(self):
        x = self.line.dequeue()
        y = self.line.dequeue()
        if y != 0:
            self.line.enqueue(x % y)
        else:
            self.line.enqueue(0)
        self.current_command_in_prg += 1

    def rget(self, register):
        x = self.line.dequeue()
        self.regs[ord(register.lower()) % 97] = x
        self.current_command_in_prg += 1

    def print(self, register=None):
        if register:
            p = self.regs[ord(register.lower()) % 97]
        else:
            p = self.line.dequeue()
        self.out.write("{}\n".format(p))
        self.current_command_in_prg += 1

    def rput(self, register):
        self.line.enqueue(self.regs[ord(register.lower()) % 97])
        self.current_command_in_prg += 1

    def printc(self, register=None):
        if register:
            p = self.regs[ord(register.lower()) % 97]
        else:
            p = self.line.dequeue()
        self.out.write(chr(p % 256))
        self.current_command_in_prg += 1

    def label(self, label):
        self.current_command_in_prg += 1

    def jmp_zero(self, register, label):
        if self.regs[ord(register.lower()) % 97] == 0:
            self.jmp(label)
        else:
            self.current_command_in_prg += 1

    def jmp_equal(self, register1, register2, label):
        if self.regs[ord(register1.lower()) % 97] == self.regs[ord(register2.lower()) % 97]:
            self.jmp(label)
        else:
            self.current_command_in_prg += 1

    def jmp_greater(self, register1, register2, label):
        if self.regs[ord(register1.lower()) % 97] > self.regs[ord(register2.lower()) % 97]:
            self.jmp(label)
        else:
            self.current_command_in_prg += 1

    def stop(self):
        self.is_program_running = False

    def do_next(self):
        assert self.current_command_in_prg != -1
        data = self.prog[self.current_command_in_prg]
        cmd = data[0]

        dispatching_table = {
            "+": self.add,
            "-": self.sub,
            "*": self.mul,
            "/": self.div,
            "%": self.mod
        }

        if cmd in dispatching_table:
            dispatching_table[cmd]()
        elif cmd == ">":
            self.rget(data[1])
        elif cmd == "<":
            self.rput(data[1])
        elif cmd == "P":
            if data[1:]:
                t = data[1:]
            else:
                t = None
            self.print(t)
        elif cmd == "C":
            if data[1:]:
                t = data[1:]
            else:
                t = None
            self.printc(t)
        elif cmd == ":":
            self.label(data[1:])
        elif cmd == "J":
            self.jmp(data[1:])
        elif cmd == "Z":
            self.jmp_zero(data[1], data[2:])
        elif cmd == "E":
            self.jmp_equal(data[1], data[2], data[3:])
        elif cmd == "G":

            self.jmp_greater(data[1], data[2], data[3:])
        elif cmd == "Q":
            self.stop()
        else:
            self.line.enqueue(data)
            self.current_command_in_prg += 1


fi = open("quack.in", 'r')
program = [_.strip() for _ in fi]
fo = open("quack.out", 'w')
quack = QuackInterpreter(program, fo)
quack.start()
