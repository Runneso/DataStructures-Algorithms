from typing import *


class Node:
    def __init__(self, value: Any, prev: Optional = None, next: Optional = None):
        self.value = value
        self.prev, self.next = prev, next


class Stack:
    def __init__(self, seq: Optional[Iterable] = ()):
        self.last = Node(None)
        if seq:
            for element in seq:
                self.push(element)

    def __repr__(self):
        stack = list()
        curr = self.last
        while curr.value:
            stack.append(curr.value)
            curr = curr.prev
        return repr(stack[::-1])

    def __str__(self):
        stack = list()
        curr = self.last
        while curr.value:
            stack.append(curr.value)
            curr = curr.prev
        return str(stack[::-1])

    def __iter__(self):
        curr = self.last
        while curr.value:
            yield curr.value
            curr = curr.prev

    def empty(self) -> bool:
        return self.last.value is None

    def push(self, value: Any) -> NoReturn:
        if value:
            curr = Node(value)
            curr.prev = self.last
            self.last = curr

    def pop(self) -> NoReturn:
        if self.last.prev:
            self.last = self.last.prev

    def top(self) -> Any:
        return self.last.value
