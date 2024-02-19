from typing import *


class Node:
    def __init__(self, value: Any, prev: Optional = None, next: Optional = None):
        self.value = value
        self.prev, self.next = prev, next


class Deque:
    def __init__(self, seq: Optional[Iterable] = ()):
        self.left, self.right = None, None
        if seq:
            for element in seq:
                self.append(element)

    def __repr__(self):
        deque = list()
        curr = self.left
        while curr is not None and curr.prev != self.right:
            deque.append(curr.value)
            curr = curr.next
        return repr(deque)

    def __str__(self):
        deque = list()
        curr = self.left
        while curr is not None and curr.prev != self.right:
            deque.append(curr.value)
            curr = curr.next
        return repr(deque)

    def __iter__(self):
        curr = self.left
        while curr is not None and curr.prev != self.right:
            yield curr.value
            curr = curr.next

    def empty(self) -> bool:
        return self.left is None or self.right is None

    def append(self, value: Any) -> NoReturn:
        curr = Node(value)
        curr.prev = self.right
        if self.right is None:
            self.left, self.right = curr, curr
        self.right.next = curr
        self.right = curr

    def append_left(self, value: Any) -> NoReturn:
        curr = Node(value)
        curr.next = self.left
        if self.left is None:
            self.right, self.left = curr, curr
        self.left.prev = curr
        self.left = curr

    def pop(self) -> NoReturn:
        if not self.empty():
            self.right = self.right.prev
            if self.right is None:
                self.left = None

    def pop_left(self) -> NoReturn:
        if not self.empty():
            self.left = self.left.next
            if self.left is None:
                self.right = None

    def get_left(self) -> Any:
        return self.left.value

    def get_right(self) -> Any:
        return self.right.value
