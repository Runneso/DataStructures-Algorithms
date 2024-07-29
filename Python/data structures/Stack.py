from abc import (
    ABC,
    abstractmethod
)
from typing import (
    TypeVar,
    Optional,
    Iterable,
    Generic,
    List
)

T = TypeVar("T")


class EmptyStackException(Exception):
    def __str__(self):
        return f"Error! Can`t pop from an empty stack."

class StackNodeInterface(ABC, Generic[T]):
    """
    Abstract base class for stack node implementations.
    """

    @abstractmethod
    def __init__(
            self,
            value: T,
            prev: Optional = None,
            next: Optional = None
    ) -> None:
        """
        Initializes the stack node.

        Time complexity: O(1)
        Memory complexity: O(1)
        """
        ...

class StackInterface(ABC, Generic[T]):
    """
    Abstract base class for stack implementations.
    """

    @abstractmethod
    def __init__(self) -> None:
        """
        Initializes the stack.

        Time complexity: O(1)
        Memory complexity: O(1)
        """
        ...

    @abstractmethod
    def __repr__(self) -> str:
        """
        Returns a string representation of the stack.

        Time complexity: O(n)
        Memory complexity: O(n)
        """
        ...

    @abstractmethod
    def __str__(self) -> str:
        """
        Returns a string representation of the stack.

        Time complexity: O(n)
        Memory complexity: O(n)
        """
        ...

    @abstractmethod
    def __iter__(self) -> Iterable[T]:
        """
        Returns an iterator over the elements of the stack.

        Time complexity: O(n)
        Memory complexity: O(1)
        """
        ...

    @abstractmethod
    def empty(self) -> bool:
        """
        Returns True if the stack is empty, False otherwise.

        Time complexity: O(1)
        Memory complexity: O(1)
        """
        ...

    @abstractmethod
    def push(self, value: T) -> None:
        """
        Pushes a value onto the stack.

        Time complexity: O(1)
        Memory complexity: O(1)
        """
        ...

    @abstractmethod
    def pop(self) -> None:
        """
        Pops the top element from the stack.

        Time complexity: O(1)
        Memory complexity: O(1)
        """
        ...

    @abstractmethod
    def top(self) -> T:
        """
        Returns the top element of the stack.

        Time complexity: O(1)
        Memory complexity: O(1)
        """
        ...



class StackNode(StackNodeInterface, Generic[T]):
    """
    A node in the stack.
    """

    def __init__(
            self,
            value: T,
            prev: Optional["StackNode"] = None,
            next: Optional["StackNode"] = None
    ) -> None:
        """
        Initializes the stack node with a value and optional previous and next nodes.

        Time complexity: O(1)
        Memory complexity: O(1)

        :param value: The value of the node.
        :param prev: The previous node in the stack.
        :param next: The next node in the stack.
        """
        self.value = value
        self.prev, self.next = prev, next


class LinkedListStack(StackInterface, Generic[T]):
    """
    A stack implementation using a linked list.
    """

    def __init__(self, seq: Optional[Iterable[T]] = None) -> None:
        """
        Initializes the stack with an optional sequence of elements.

        Time complexity: O(n)
        Memory complexity: O(n)

        :param seq: An optional sequence of elements to initialize the stack with.
        """
        self.last = StackNode(None)
        if seq is not None:
            for element in seq:
                self.push(element)

    def __repr__(self) -> str:
        """
        Returns a string representation of the stack.

        Time complexity: O(n)
        Memory complexity: O(n)
        """
        return repr(self.__get_list_stack())

    def __str__(self) -> str:
        """
        Returns a string representation of the stack.

        Time complexity: O(n)
        Memory complexity: O(n)
        """
        return str(self.__get_list_stack())

    def __iter__(self) -> Iterable[T]:
        """
        Returns an iterator over the elements of the stack.

        Time complexity: O(n)
        Memory complexity: O(1)
        """
        curr = self.last
        while curr.value:
            yield curr.value
            curr = curr.prev

    def empty(self) -> bool:
        """
        Returns True if the stack is empty, False otherwise.

        Time complexity: O(1)
        Memory complexity: O(1)
        """
        return self.last.value is None

    def push(self, value: T) -> None:
        """
        Pushes a value onto the stack.

        Time complexity: O(1)
        Memory complexity: O(1)

        :param value: The value to push onto the stack.
        """
        if value:
            curr = StackNode(value)
            curr.prev = self.last
            self.last = curr

    def pop(self) -> None:
        """
        Pops the top element from the stack.

        Time complexity: O(1)
        Memory complexity: O(1)
        """
        if self.last.prev is None:
            raise EmptyStackException()
        self.last = self.last.prev

    def top(self) -> T:
        """
        Returns the top element of the stack.

        Time complexity: O(1)
        Memory complexity: O(1)
        """
        if self.empty():
            raise EmptyStackException()
        return self.last.value

    def __get_list_stack(self) -> List[T]:
        """
        Returns a list representation of the stack.

        Time complexity: O(n)
        Memory complexity: O(n)
        """
        stack = list()
        curr = self.last
        while curr.value:
            stack.append(curr.value)
            curr = curr.prev
        return stack[::-1]
