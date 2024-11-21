#include <bits/stdc++.h>

using namespace std;

constexpr size_t N = 100;
constexpr size_t TESTS = 100'000;
constexpr int64_t MAX_VALUE = 1000;
constexpr int64_t MIN_VALUE = -MAX_VALUE;

template<class T>
size_t median(vector<T> &array, size_t left, size_t right) {
    vector<int64_t> values = {array[left], array[right], array[(left + right) / 2]};
    int64_t minimum = abs(array[left] - values[1]) + abs(array[left] - values[2]);
    size_t min_index = left;

    for (size_t index = left + 1; index <= right; index++) {
        int64_t curr = 0;
        for (int64_t value: values) {
            curr += abs(array[index] - value);
        }
        if (curr < minimum) {
            minimum = curr;
            min_index = index;
        }
    }
    return min_index;
}

template<class T>
size_t partition(vector<T> &array, size_t left, size_t right) {
    T pivot = array[(left + right) / 2];

    while (left <= right) {
        while (array[left] < pivot) {
            left++;
        }
        while (array[right] > pivot) {
            right--;
        }
        if (left >= right) {
            break;
        }
        swap(array[left++], array[right--]);
    }
    return right;
}

template<class T>
void quickSortRecursion(vector<T> &array, size_t left, size_t right) {
    if (left < right) {
        size_t med = median(array, left, right);
        swap(array[med], array[(left + right) / 2]);

        size_t pivot = partition(array, left, right);
        quickSortRecursion(array, left, pivot);
        quickSortRecursion(array, pivot + 1, right);
    }
}

template<class T>
void quickSort(vector<T> &array) {
    quickSortRecursion(array, 0, array.size() - 1);
}

void test() {
    vector<int64_t> array;

    for (size_t index = 0; index < N; ++index) {
        array.push_back((rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE);
    }

    vector<int64_t> copy_array(array);


    quickSort(array);
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
