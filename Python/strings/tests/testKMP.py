import unittest
from KMP import KMP
from string import ascii_lowercase
from random import choice


class TestKMP(unittest.TestCase):

    def test(self):
        for _ in range(10):
            string, pattern = str(), str()
            for _ in range(10 ** 5):
                string += choice(ascii_lowercase)
            for _ in range(3):
                pattern += choice(ascii_lowercase)
            correct = 0
            n, m = len(string), len(pattern)
            for index in range(n - 3):
                if string[index:index + 3] == pattern:
                    correct += 1
            self.assertEquals(correct, KMP(string, pattern))


if __name__ == "__main__":
    unittest.main()
