from typing import *


def get_prefix(string: str) -> List[int]:
    n = len(string)
    prefix = [0] * (n + 1)
    prefix[0] = -1
    for index in range(1, n + 1):
        curr = prefix[index - 1]
        while curr != -1 and string[curr] != string[index - 1]:
            curr = prefix[curr]
        prefix[index] = curr + 1
    return prefix


def KMP(string: str, pattern: str) -> int:
    count = 0
    n, m = len(string), len(pattern)
    together = pattern + "#" + string
    prefix = get_prefix(together)
    for index in range(n + m + 2):
        if prefix[index] == m:
            count += 1
    return count
