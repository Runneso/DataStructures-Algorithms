import unittest
from BinaryHeap import BinaryHeap
from random import randint


class TestBinaryHeap(unittest.TestCase):

    def test_insert(self):
        correct = list()
        heap = BinaryHeap()
        for _ in range(100):
            curr = randint(-10 ** 9, 10 ** 9)
            correct.append(curr), heap.insert(curr)
        self.assertEquals(sorted(correct), sorted(heap))

    def test_pop(self):
        correct = [randint(-10 ** 9, 10 ** 9) for _ in range(100)]
        heap = BinaryHeap(correct)
        for _ in range(50):
            correct.remove(min(correct)), heap.pop()
        self.assertEquals(sorted(correct), sorted(heap))

    def test_get_min(self):
        correct = [randint(-10 ** 9, 10 ** 9) for _ in range(100)]
        heap = BinaryHeap(correct)
        for _ in range(100):
            action = randint(0, 1)
            curr = randint(-10 ** 9, 10 ** 9)
            if action:
                correct.append(curr), heap.insert(curr)
            else:
                correct.remove(min(correct)), heap.pop()
            self.assertEquals(min(correct), heap.get_min())


if __name__ == "__main__":
    unittest.main()
