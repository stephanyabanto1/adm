class Child:
    def __init__(self) -> None:
        pass

    def run(self):
        print("run")

class Parent:
    def __init__(self) -> None:
        self.child = Child()
    
    def run(self):
        self.child.run()


p = Parent()

p.run()

