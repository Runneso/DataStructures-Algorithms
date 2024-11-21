#include <bits/stdc++.h>

using namespace std;

template<class T>
struct BinaryHeap {
    vector<T> heap;

    function<bool(T, T)> compare;

    BinaryHeap() {
        heap = vector<T>();
        compare = [](T a, T b) {
            return a > b;
        };
    }

    explicit BinaryHeap(function<bool(T, T)> compareFunc) {
        heap = vector<T>();
        compare = compareFunc;
    }

    void push(T value) {
        heap.push_back(value);
        int64_t index = heap.size() - 1;

        while (index > 0 && compare(heap[index], heap[(index - 1) / 2])) {
            swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    T top() const {
        if (!heap.empty()) {
            return heap[0];
        }
        return T();
    }

    void pop() {
        if (heap.empty()) {
            return;
        }
        swap(heap[0], heap.back());
        heap.pop_back();
        const size_t n = heap.size();
        size_t index_i = 0;

        while (2 * index_i + 1 < n) {
            size_t index_j = 2 * index_i + 1;
            size_t right_child = 2 * index_i + 2;

            if (right_child < n && compare(heap[right_child], heap[index_j])) {
                index_j = right_child;
            }

            if (compare(heap[index_i], heap[index_j]) || heap[index_i] == heap[index_j]) {
                break;
            }

            swap(heap[index_i], heap[index_j]);
            index_i = index_j;
        }
    }

    [[nodiscard]] bool empty() const {
        return heap.empty();
    }

    [[nodiscard]] size_t size() const {
        return heap.size();
    }
};
