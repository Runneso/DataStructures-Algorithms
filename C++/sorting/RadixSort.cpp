#include <bits/stdc++.h>

using namespace std;

constexpr size_t N = 100;
constexpr size_t TESTS = 100'000;
constexpr int64_t MAX_VALUE = 1000;
constexpr int64_t MIN_VALUE = 0;


template<typename T>
void countSort(vector<T> &array, int64_t exp) {
    int64_t n = array.size();
    vector<T> result(n, 0);
    vector<int64_t> count(10, 0);

    for (T element: array) {
        const int64_t index = element / exp;
        ++count[index % 10];
    }


    for (int64_t index = 1; index < 10; ++index) {
        count[index] += count[index - 1];
    }

    int64_t index = n - 1;

    while (index >= 0) {
        const int64_t digit = array[index] / exp;
        result[count[digit % 10] - 1] = array[index];
        --count[digit % 10];
        --index;
    }

    for (int64_t index=0; index<n; ++index) {
        array[index] = result[index];
    }
}

template<class T>
void radixSort(vector<T> &array) {
    int64_t exp = 1;
    T maximum = array[0];

    for (T element: array) {
        maximum = max(maximum, element);
    }

    while (maximum / exp > 0) {
        countSort(array, exp);
        exp *= 10;
    }
}

void test() {
    vector<int64_t> array;

    for (size_t index = 0; index < N; ++index) {
        array.push_back((rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE);
    }

    vector<int64_t> copy_array(array);

    radixSort(array);
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
