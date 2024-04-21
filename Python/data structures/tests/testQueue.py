import unittest
from Queue import Queue
from random import randint


class TestQueue(unittest.TestCase):

    def test_push(self):
        correct = list()
        queue = Queue()
        for _ in range(100):
            curr = randint(1, 10 ** 9)
            queue.push(curr), correct.append(curr)
        queue = list(queue)
        self.assertEquals(queue, correct)

    def test_pop(self):
        correct = [randint(1, 10 ** 9) for _ in range(100)]
        queue = Queue(correct)
        for _ in range(50):
            correct.pop(0), queue.pop()
        queue = list(queue)
        self.assertEquals(queue, correct)

    def test_top(self):
        correct = [randint(1, 10 ** 9) for _ in range(100)]
        queue = Queue(correct)
        for _ in range(50):
            correct.pop(0), queue.pop()
            self.assertEquals(queue.top(), correct[0])

    def test_empty(self):
        for _ in range(100):
            empty = randint(0, 1)
            correct = list()
            queue = Queue()
            if empty:
                self.assertEquals(queue.empty(), len(correct) == 0)
            else:
                correct.append(1), queue.push(1)
                self.assertEquals(queue.empty(), len(correct) == 0)


if __name__ == "__main__":
    unittest.main()
