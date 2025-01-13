#include <bits/stdc++.h>

using namespace std;

template<class T>
struct SegmentTree {
    int64_t n;
    vector<T> tree;

    function<T(T, T)> action;
    T null;

    explicit SegmentTree(vector<T> &seq) {
        this->n = seq.size();
        this->tree.assign(this->n * 4, 0);

        this->action = [&](T a, T b) {
            return a + b;
        };

        this->null = T();

        this->build(seq, 0, this->n - 1, 0);
    }


    explicit SegmentTree(vector<T> &seq, T action(T, T), T null) {
        this->n = seq.size();
        this->tree.assign(this->n * 4, 0);

        this->action = action;
        this->null = null;

        this->build(seq, 0, this->n - 1, 0);
    }

    void build(vector<T> &seq, const int64_t left, const int64_t right, const int64_t index) {
        if (left == right) {
            this->tree[index] = seq[left];
            return;
        }

        const int64_t mid = (left + right) / 2;

        this->build(seq, left, mid, 2 * index + 1);
        this->build(seq, mid + 1, right, 2 * index + 2);

        this->tree[index] = this->action(this->tree[2 * index + 1], this->tree[2 * index + 2]);
    }

    void update(const int64_t left, const int64_t right, const int64_t index, const int64_t pos, const int64_t val) {
        if (left == right) {
            this->tree[index] = val;
            return;
        }

        const int64_t mid = (left + right) / 2;

        if (pos <= mid) {
            this->update(left, mid, 2 * index + 1, pos, val);
        } else {
            this->update(mid + 1, right, 2 * index + 2, pos, val);
        }

        this->tree[index] = this->action(this->tree[2 * index + 1], this->tree[2 * index + 2]);
    }

    T sum(const int64_t left, const int64_t right, const int64_t index, const int64_t curr_left,
          const int64_t curr_right) {
        if (curr_right < left || curr_left > right) {
            return this->null;
        }

        if (curr_left <= left && right <= curr_right) {
            return this->tree[index];
        }

        const int64_t mid = (left + right) / 2;

        T left_sum = this->sum(left, mid, 2 * index + 1, curr_left, curr_right);
        T right_sum = this->sum(mid + 1, right, 2 * index + 2, curr_left, curr_right);

        return this->action(left_sum, right_sum);
    }

    void modify(const int64_t pos, T val) {
        this->update(0, this->n - 1, 0, pos, val);
    }

    T query(const int64_t l, const int64_t r) {
        return this->sum(0, this->n - 1, 0, l, r);
    }
};
