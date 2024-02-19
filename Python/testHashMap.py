import unittest
from HashMap import HashMap
from random import randint


class TestHashMap(unittest.TestCase):

    def test_set_get(self):
        correct = dict()
        hashmap = HashMap()
        for _ in range(10 ** 3):
            key, value = randint(1, 100), randint(1, 10 ** 9)
            correct[key] = value
            hashmap[key] = value
            self.assertEquals((correct.keys()), hashmap.get_keys())
        for key in range(10 ** 3):
            self.assertEquals(correct.get(key, -1), hashmap.get(key, -1))

    def test_contain(self):
        correct = dict()
        hashmap = HashMap()
        for _ in range(10 ** 3):
            key, value = randint(1, 100), randint(1, 10 ** 9)
            correct[key] = value
            hashmap[key] = value
        for key in range(10 ** 3):
            self.assertEquals(key in correct, key in hashmap)


if __name__ == "__main__":
    unittest.main()
