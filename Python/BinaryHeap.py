from typing import *


class BinaryHeap:
    def __init__(self, seq: Optional[Iterable] = ()):
        self.heap = list()
        if seq:
            for element in seq:
                self.insert(element)

    def __str__(self):
        return str(self.heap)

    def __repr__(self):
        return repr(self.heap)

    def __iter__(self):
        return iter(self.heap)

    def __len__(self):
        return len(self.heap)

    def insert(self, value: Any) -> NoReturn:
        self.heap.append(value)
        n = len(self.heap)
        i = n - 1
        while i > 0 and self.heap[i] < self.heap[((i - 1) // 2)]:
            self.heap[i], self.heap[(i - 1) // 2] = self.heap[(i - 1) // 2], self.heap[i]
            i = (i - 1) // 2

    def pop(self) -> Any:
        if not self.heap:
            return None
        self.heap[0], self.heap[-1] = self.heap[-1], self.heap[0]
        result = self.heap.pop()
        n = len(self.heap)
        i = 0
        while 2 * i + 1 < n:
            j = 2 * i + 1
            if 2 * i + 2 < n and self.heap[2 * i + 2] < self.heap[j]:
                j = 2 * i + 2
            if self.heap[i] <= self.heap[j]:
                break
            else:
                self.heap[i], self.heap[j] = self.heap[j], self.heap[i]
                i = j
        return result

    def get_min(self) -> Any:
        if not self.heap:
            return None
        return self.heap[0]
