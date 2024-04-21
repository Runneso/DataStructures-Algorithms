from typing import *
from HashSet import HashSet


class Node:
    def __init__(self, value: Any, prev: Optional = None, next: Optional = None):
        self.value = value
        self.prev, self.next = prev, next


class Pair:
    def __init__(self, key: Any, value: Any):
        self.key = key
        self.value = value

    def __str__(self):
        return f"({self.key}, {self.value})"

    def __repr__(self):
        return f"({self.key}, {self.value})"


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

    def find(self, key: Any) -> Any:
        curr = self.start
        while curr:
            if curr.value.key == key:
                return curr.value.value
            curr = curr.next

    def new_value(self, key: Any, value: Any):
        curr = self.start
        while curr:
            if curr.value.key == key:
                curr.value.value = value
                return
            curr = curr.next


class HashMap:
    START_SIZE = 10

    def __init__(self, seq: Optional[Iterable[Tuple]] = ()):
        self.hashmap = [LinkedList() for _ in range(self.START_SIZE)]
        self.keys = HashSet()
        self.size, self.capacity = 0, self.START_SIZE
        self.size_ratio_upper = 0.75
        if seq:
            for element in seq:
                if len(element) == 2:
                    key, value = element
                    self[key] = value

    def __repr__(self):
        if self.empty():
            return "{}"
        result = "{"
        for pair in self.get_items():
            result += f"{str(pair.key)}: {str(pair.value)}, "
        return result[:-2] + "}"

    def __str__(self):
        if self.empty():
            return "{}"
        result = "{"
        for pair in self.get_items():
            result += f"{str(pair.key)}: {str(pair.value)}, "
        return result[:-2] + "}"

    def __setitem__(self, key: Any, value: Any):
        if key not in self.keys:
            self.size += 1
            self.keys.add(key)
        if self.size / self.capacity >= self.size_ratio_upper:
            self.capacity *= 2
            elements = [Pair(key, value)]
            for bucket in self.hashmap:
                elements.extend(bucket)
            self.hashmap = [LinkedList() for _ in range(self.capacity)]
            for pair in elements:
                key, value = pair.key, pair.value
                index = hash(key) % self.capacity
                if self.hashmap[index].find(key) is not None:
                    self.hashmap[index].new_value(key, value)
                else:
                    self.hashmap[index].add(pair)
        else:
            index = hash(key) % self.capacity
            pair = Pair(key, value)
            if self.hashmap[index].find(key) is not None:
                self.hashmap[index].new_value(key, value)
            else:
                self.hashmap[index].add(pair)

    def __getitem__(self, key: Any):
        if key in self.keys:
            index = hash(key) % self.capacity
            return self.hashmap[index].find(key)

    def __iter__(self):
        return iter(self.keys)

    def __contains__(self, key: Any):
        return key in self.keys

    def __len__(self):
        return self.size

    def get(self, key: Any, default: Optional[Any] = None):
        if key not in self.keys:
            return default
        return self[key]

    def empty(self) -> bool:
        return self.size == 0

    def get_keys(self) -> Set:
        return set(self.keys)

    def get_values(self) -> List:
        values = list()
        for bucket in self.hashmap:
            for pair in bucket:
                values.append(pair.value)
        return values

    def get_items(self) -> List:
        items = list()
        for bucket in self.hashmap:
            for pair in bucket:
                items.append(pair)
        return items
