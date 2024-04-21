from typing import *


class Node:
    def __init__(self, value: Any, prev: Optional = None, next: Optional = None):
        self.value = value
        self.prev, self.next = prev, next


class LinkedList:
    def __init__(self):
        self.start = None

    def __repr__(self):
        linkedList = list()
        curr = self.start
        while curr:
            linkedList.append(curr.value)
            curr = curr.next
        return repr(linkedList[::-1])

    def __str__(self):
        linkedList = list()
        curr = self.start
        while curr:
            linkedList.append(curr.value)
            curr = curr.next
        return str(linkedList[::-1])

    def __contains__(self, value: Any):
        curr = self.start
        while curr:
            if curr.value == value:
                return True
            curr = curr.next
        return False

    def __iter__(self):
        curr = self.start
        while curr:
            yield curr.value
            curr = curr.next

    def empty(self) -> bool:
        return self.start is None

    def add(self, value: Any) -> NoReturn:
        curr = Node(value)
        if self.start is None:
            self.start = curr
        else:
            curr.next = self.start
            self.start = curr

    def remove(self, value: Any) -> NoReturn:
        if not self.empty() and value in self:
            curr = self.start
            if self.start.value == value:
                if self.start is not None:
                    self.start = self.start.next
                return
            while curr and curr.next.value != value:
                curr = curr.next
            if curr is not None:
                curr.next = curr.next.next


class HashSet:
    START_SIZE = 10

    def __init__(self, seq: Optional[Iterable] = ()):
        self.hashset = [LinkedList() for _ in range(self.START_SIZE)]
        self.size, self.capacity = 0, self.START_SIZE
        self.size_ratio_upper = 0.75
        self.size_ratio_lower = 0.50
        if seq:
            for element in seq:
                self.add(element)

    def __repr__(self):
        if self.empty():
            return "{}"
        result = "{"
        for bucket in self.hashset:
            for element in bucket:
                result += f"{str(element)}, "
        return result[:-2] + "}"

    def __str__(self):
        if self.empty():
            return "{}"
        result = "{"
        for bucket in self.hashset:
            for element in bucket:
                result += f"{str(element)}, "
        return result[:-2] + "}"

    def __iter__(self):
        for bucket in self.hashset:
            for element in bucket:
                yield element

    def __contains__(self, value: Any):
        index = hash(value) % self.capacity
        return value in self.hashset[index]

    def __len__(self):
        return self.size

    def empty(self):
        return self.size == 0

    def add(self, value: Any) -> NoReturn:
        if value not in self:
            self.size += 1
            if self.size / self.capacity >= self.size_ratio_upper:
                self.capacity *= 2
                elements = [value]
                for bucket in self.hashset:
                    elements.extend(bucket)
                self.hashset = [LinkedList() for _ in range(self.capacity)]
                for element in elements:
                    index = hash(element) % self.capacity
                    self.hashset[index].add(element)
            else:
                index = hash(value) % self.capacity
                self.hashset[index].add(value)

    def remove(self, value: Any) -> NoReturn:
        if value in self:
            self.size -= 1
            if self.size / self.capacity <= self.size_ratio_lower:
                self.capacity //= 2
                elements = list()
                for bucket in self.hashset:
                    elements.extend(bucket)
                elements.remove(value)
                self.hashset = [LinkedList() for _ in range(self.capacity)]
                for element in elements:
                    index = hash(element) % self.capacity
                    self.hashset[index].add(element)
            else:
                index = hash(value) % self.capacity
                self.hashset[index].remove(value)

