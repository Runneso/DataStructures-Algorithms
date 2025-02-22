#include <bits/stdc++.h>

using namespace std;

template<class T>
struct SparseTable {
    size_t n;
    vector<vector<T> > table;
    T neutral;
    function<T(T, T)> action;

    explicit SparseTable(
        vector<T> &array,
        T neutral = LLONG_MAX,
        T action(T, T) = [](T x, T y) {
            return min(x, y);
        }
    ) {
        if (array.empty()) {
            return;
        }

        this->n = array.size();

        size_t maxPow = __lg(n) + 1;

        this->neutral = neutral;
        this->action = action;
        this->table.assign(n, vector<T>(maxPow, neutral));


        for (size_t index = 0; index < n; index++) {
            this->table[index][0] = array[index];
        }

        for (size_t k = 1; k < maxPow; k++) {
            for (size_t index = 0; index + (1 << k) <= n; index++) {
                this->table[index][k] = action(this->table[index][k - 1], this->table[index + (1 << (k - 1))][k - 1]);
            }
        }
    }

    T query(size_t l, const size_t r) {
        size_t t = __lg(r - l + 1);
        return action(this->table[l][t], this->table[r - (1 << t) + 1][t]);
    }
};
