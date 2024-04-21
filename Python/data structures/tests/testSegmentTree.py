import unittest
from SegmentTree import SegmentTree
from random import randint


class TestSegmentTree(unittest.TestCase):

    def test_sum_update(self):
        n = 100
        correct = [randint(-10 ** 9, 10 ** 9) for _ in range(n)]
        tree = SegmentTree(correct)
        for _ in range(100):
            action = randint(0, 1)
            if action:
                left = randint(0, n - 1)
                right = randint(left, n - 1)
                correct_sum = 0
                for index in range(left, right + 1):
                    correct_sum += correct[index]
                self.assertEquals(correct_sum, tree.sum(0, n - 1, 0, left, right))
            else:
                pos, value = randint(0, n - 1), randint(-10 ** 9, 10 ** 9)
                correct[pos] = value
                tree.update(0, n - 1, 0, pos, value)
