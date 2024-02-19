import unittest
from HashSet import HashSet
from random import randint


class TestHashSet(unittest.TestCase):

    def test_add(self):
        correct = set()
        hashset = HashSet()
        for _ in range(100):
            curr = randint(1, 10 ** 9)
            correct.add(curr), hashset.add(curr)
        self.assertEquals(sorted(correct), sorted(hashset))

    def test_remove(self):
        correct = {num for num in range(100)}
        hashset = HashSet(correct)
        for _ in range(100):
            curr = randint(0, 99)
            correct.discard(curr), hashset.remove(curr)
        self.assertEquals(sorted(correct), sorted(hashset))

    def test_contain(self):
        correct = set()
        hashset = HashSet()
        for _ in range(10 ** 4):
            curr = randint(1, 10 ** 3)
            correct.add(curr), hashset.add(curr)
        for num in range(1, 10 ** 3):
            self.assertEquals(num in correct, num in hashset)


if __name__ == "__main__":
    unittest.main()
