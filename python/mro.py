class A:
    x = 1

    def __init__(self):
        self.x_x = self.x


class B():
    x = 1

    def __init__(self):
        self.x_x = self.x


class C(B, A):
    #  x = 5

    def __init__(self):
        self.x_x = self.x
        super().__init__()


c = C()
print(c.x_x)
