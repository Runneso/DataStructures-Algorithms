#include <bits/stdc++.h>

using namespace std;

constexpr size_t N = 100;
constexpr size_t TESTS = 100'000;
constexpr int64_t MAX_VALUE = 1000;
constexpr int64_t MIN_VALUE = -MAX_VALUE;

template<class T>
void merge(size_t left, const size_t mid, const size_t right, vector<T> &array) {
    vector<T> left_array, right_array;

    for (size_t index = left; index < mid; ++index) {
        left_array.push_back(array[index]);
    }
    for (size_t index = mid; index < right; ++index) {
        right_array.push_back(array[index]);
    }

    size_t i = 0, j = 0;
    const size_t n = left_array.size();
    const size_t m = right_array.size();

    while (i < n && j < m) {
        if (left_array[i] <= right_array[j]) {
            array[left++] = left_array[i++];
        } else {
            array[left++] = right_array[j++];
        }
    }
    while (i < n) {
        array[left++] = left_array[i++];
    }
    while (j < m) {
        array[left++] = right_array[j++];
    }
}

template<class T>
void mergeSortRecursion(size_t left, size_t right, vector<T> &array) {
    if (left + 1 >= right) {
        return;
    }
    size_t mid = (left + right) / 2;
    mergeSortRecursion(left, mid, array);
    mergeSortRecursion(mid, right, array);
    merge(left, mid, right, array);
}

template<class T>
void mergeSortIterative(vector<T> &array) {
    const size_t n = array.size();
    for (size_t index_i = 1; index_i <= n; index_i *= 2) {
        for (size_t index_j = 0; index_j <= n - index_i; index_j += 2 * index_i) {
            merge(index_j, index_i + index_j, min(index_j + 2 * index_i, n), array);
        }
    }
}

template<class T>
void mergeSort(vector<T> &array) {
    mergeSortIterative(array);
    // mergeSortRecursion(0, array.size(), array);
}

void test() {
    vector<int64_t> array;

    for (size_t index = 0; index < N; ++index) {
        array.push_back((rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE);
    }

    vector<int64_t> copy_array(array);

    mergeSort(array);
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
