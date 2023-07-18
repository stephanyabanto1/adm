class Child:
    def __init__(self) -> None:
        pass

    def run(self):
        return "run"

class Parent:
    def __init__(self) -> None:
        self.child = Child()
    
    def run(self):
        return self.child.run()


p = Parent()

print(p.run())

