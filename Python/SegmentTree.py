from typing import *


class SegmentTree:
    def __init__(self, seq: Iterable = ()):
        seq = list(seq)
        self.n = len(seq)
        self.tree = [0] * 4 * self.n
        self.build(seq, 0, self.n - 1, 0)

    def __repr__(self):
        return repr(self.tree[:self.n])

    def __str__(self):
        return str(self.tree[:self.n])

    def __iter__(self):
        return iter(self.tree[:self.n])

    def __len__(self):
        return self.n

    def build(self, seq: List, left: int, right: int, index: int) -> None:
        if left == right:
            self.tree[index] = seq[left]
            return

        mid = (left + right) // 2

        self.build(seq, left, mid, 2 * index + 1)
        self.build(seq, mid + 1, right, 2 * index + 2)

        self.tree[index] = self.tree[2 * index + 1] + self.tree[2 * index + 2]

    def update(self, left: int, right: int, index: int, pos: int, val: Any) -> None:
        if left == right:
            self.tree[index] = val
            return

        mid = (left + right) // 2

        if pos <= mid:
            self.update(left, mid, 2 * index + 1, pos, val)
        else:
            self.update(mid + 1, right, 2 * index + 2, pos, val)

        self.tree[index] = self.tree[2 * index + 1] + self.tree[2 * index + 2]

    def sum(self, left: int, right: int, index: int, curr_left: int, curr_right: int) -> int:
        if curr_right < left or curr_left > right:
            return 0

        if curr_left <= left and right <= curr_right:
            return self.tree[index]

        mid = (left + right) // 2
        left_sum = self.sum(left, mid, 2 * index + 1, curr_left, curr_right)
        right_sum = self.sum(mid + 1, right, 2 * index + 2, curr_left, curr_right)
        return left_sum + right_sum
