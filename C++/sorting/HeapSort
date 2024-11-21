#include <bits/stdc++.h>

using namespace std;

constexpr size_t N = 100;
constexpr size_t TESTS = 100'000;
constexpr int64_t MAX_VALUE = 1000;
constexpr int64_t MIN_VALUE = -MAX_VALUE;

template<class T>
void siftDown(vector<T> &array, size_t n, size_t index) {
    while (2 * index + 1 < n) {
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;
        size_t pivot = left;
        if (right < n && array[right] > array[left]) {
            pivot = right;
        }
        if (array[index] >= array[pivot]) {
            break;
        }
        swap(array[index], array[pivot]);
        index = pivot;
    }
}

template<class T>
void heapSort(vector<T> &array) {
    int64_t n = array.size();
    for (int64_t index = n / 2 - 1; index >= 0; --index) {
        siftDown(array, n, index);
    }
    for (int64_t index = n - 1; index >= 0; --index) {
        swap(array[0], array[index]);
        siftDown(array, index, 0);
    }
}

void test() {
    vector<int64_t> array;

    for (size_t index = 0; index < N; ++index) {
        array.push_back((rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE);
    }

    vector<int64_t> copy_array(array);

    heapSort(array);
    ranges::sort(copy_array);

    assert(copy_array == array);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    srand(time(nullptr));

    size_t tests = TESTS;
    while (tests--) {
        test();
    }
}
