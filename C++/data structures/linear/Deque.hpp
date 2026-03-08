#pragma once
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

#pragma GCC optimize("Ofast,unroll-loops")

#define ll long long int
#define ld long double

#define PI acos(-1)
#define inf LONG_LONG_MAX
#define MOD (1'000'000'000+7)
#define MOD_ (1'000'000'000+9)
#define BASE (911382323)
#define BASE_ (972663749)
#define EPS 1e-9
#define all(x) x.begin(), x.end()
#define print(x) for (auto element : x) cout << element << " ";
#define endl "\n"

#define I_AM_OUTSIDER = true;
#define RAMAZAN_RAKHMATULLIN_FAN_CLUB = true;


namespace mydeque {
    struct Node {
        Node *left, *right;
        ll value;

        Node(Node *left, Node *right, ll value): left(left), right(right), value(value) {
        }
    };
}

struct Deque {
    struct Iterator {
        mydeque::Node *ptr;

        explicit Iterator(mydeque::Node *p) : ptr(p) {
        }

        ll &operator*() const {
            return ptr->value;
        }

        Iterator &operator++() {
            ptr = ptr->right;
            return *this;
        }

        bool operator!=(const Iterator &other) const {
            return ptr != other.ptr;
        }
    };

    mydeque::Node *front = nullptr, *back = nullptr;
    size_t size = 0;

    ll get_front() const {
        assert(!empty());
        return front->value;
    }

    ll get_back() const {
        assert(!empty());
        return back->value;
    }

    size_t get_size() const {
        return size;
    }

    bool empty() const {
        return size == 0;
    }

    void push_back(ll value) {
        if (empty()) {
            mydeque::Node *new_node = new mydeque::Node(nullptr, nullptr, value);
            front = new_node;
            back = new_node;
        } else {
            mydeque::Node *new_back = new mydeque::Node(back, nullptr, value);
            back->right = new_back;
            back = new_back;
        }
        size++;
    }

    void pop_back() {
        if (empty()) {
            return;
        }
        size--;
        if (empty()) {
            delete back;
            front = nullptr;
            back = nullptr;
        } else {
            mydeque::Node *old = back;
            back = back->left;
            back->right = nullptr;
            delete old;
        }
    }

    void push_front(ll value) {
        if (empty()) {
            mydeque::Node *new_node = new mydeque::Node(nullptr, nullptr, value);
            front = new_node;
            back = new_node;
        } else {
            mydeque::Node *new_front = new mydeque::Node(nullptr, front, value);
            front->left = new_front;
            front = new_front;
        }
        size++;
    }

    void pop_front() {
        if (empty()) {
            return;
        }
        size--;
        if (empty()) {
            delete front;
            front = nullptr;
            back = nullptr;
        } else {
            mydeque::Node *old = front;
            front = front->right;
            front->left = nullptr;
            delete old;
        }
    }

    Iterator begin() const {
        return Iterator(front);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }
};
