import unittest
from Deque import Deque
from random import randint


class TestDeque(unittest.TestCase):

    def test_append(self):
        correct = list()
        deque = Deque()
        for _ in range(100):
            curr = randint(1, 10 ** 9)
            deque.append(curr)
            correct.append(curr)
        deque = list(deque)
        self.assertEquals(deque, correct)

    def test_append_left(self):
        correct = list()
        deque = Deque()
        for _ in range(100):
            curr = randint(1, 10 ** 9)
            deque.append_left(curr)
            correct.insert(0, curr)
        deque = list(deque)
        self.assertEquals(deque, correct)

    def test_pop(self):
        correct = [randint(1, 10 ** 9) for _ in range(100)]
        deque = Deque(correct)
        for _ in range(50):
            correct.pop(), deque.pop()
        deque = list(deque)
        self.assertEquals(deque, correct)

    def test_pop_left(self):
        correct = [randint(1, 10 ** 9) for _ in range(100)]
        deque = Deque(correct)
        for _ in range(50):
            correct.pop(0), deque.pop_left()
        deque = list(deque)
        self.assertEquals(deque, correct)

    def test_right_left(self):
        correct = [randint(1, 10 ** 9) for _ in range(100)]
        deque = Deque(correct)
        for _ in range(99):
            side = randint(0, 1)
            if side:
                correct.pop(0), deque.pop_left()
            else:
                correct.pop(), deque.pop()
            self.assertEquals(deque.get_left(), correct[0])
            self.assertEquals(deque.get_right(), correct[-1])

    def test_empty(self):
        for _ in range(100):
            empty = randint(0, 1)
            correct = list()
            deque = Deque()
            if empty:
                self.assertEquals(deque.empty(), len(correct) == 0)
            else:
                correct.append(1), deque.append(1)
                self.assertEquals(deque.empty(), len(correct) == 0)


if __name__ == "__main__":
    unittest.main()
