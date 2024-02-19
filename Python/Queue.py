from typing import *


class Node:
    def __init__(self, value: Any, prev: Optional = None, next: Optional = None):
        self.value = value
        self.prev, self.next = prev, next


class Queue:
    def __init__(self, seq: Optional[Iterable] = ()):
        self.head, self.tail = None, None
        if seq:
            for element in seq:
                self.push(element)

    def __repr__(self):
        queue = list()
        curr = self.head
        while curr:
            queue.append(curr.value)
            curr = curr.next
        return repr(queue)

    def __str__(self):
        queue = list()
        curr = self.head
        while curr:
            queue.append(curr.value)
            curr = curr.next
        return str(queue)

    def __iter__(self):
        curr = self.head
        while curr:
            yield curr.value
            curr = curr.next

    def empty(self) -> bool:
        return self.head is None

    def push(self, value: Any) -> NoReturn:
        curr = Node(value)
        if self.tail is None:
            self.head, self.tail = curr, curr
        self.tail.next = curr
        self.tail = curr

    def pop(self) -> NoReturn:
        if not self.empty():
            self.head = self.head.next
            if self.head is None:
                self.tail = None

    def top(self) -> Any:
        return self.head.value
