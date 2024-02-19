import unittest
from Stack import Stack
from random import randint


class TestStack(unittest.TestCase):

    def test_push(self):
        correct = list()
        stack = Stack()
        for _ in range(100):
            curr = randint(1, 10 ** 9)
            stack.push(curr), correct.append(curr)
        stack = list(stack)
        self.assertEquals(stack[::-1], correct)

    def test_pop(self):
        correct = [randint(1, 10 ** 9) for _ in range(100)]
        stack = Stack(correct)
        for _ in range(50):
            correct.pop(), stack.pop()
        stack = list(stack)
        self.assertEquals(stack[::-1], correct)

    def test_top(self):
        correct = [randint(1, 10 ** 9) for _ in range(100)]
        stack = Stack(correct)
        for _ in range(50):
            correct.pop(), stack.pop()
            self.assertEquals(stack.top(), correct[-1])

    def test_empty(self):
        for _ in range(100):
            empty = randint(0, 1)
            correct = list()
            stack = Stack()
            if empty:
                self.assertEquals(stack.empty(), len(correct) == 0)
            else:
                correct.append(1), stack.push(1)
                self.assertEquals(stack.empty(), len(correct) == 0)


if __name__ == "__main__":
    unittest.main()
