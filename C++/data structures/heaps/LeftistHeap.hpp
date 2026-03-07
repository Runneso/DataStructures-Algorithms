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

namespace leftistHeap {
    struct Node {
        Node *left, *right;
        ll key;
        size_t dist = 0;

        Node(Node *left, Node *right, ll key) : left(left), right(right), key(key), dist(1) {
        }
    };

    int getDist(Node *root) {
        return root ? root->dist : 0;
    }

    Node *merge(Node *x, Node *y) {
        if (x == nullptr) {
            return y;
        }
        if (y == nullptr) {
            return x;
        }

        if (x->key > y->key) {
            swap(x, y);
        }

        x->right = merge(x->right, y);


        if (getDist(x->right) > getDist(x->left)) {
            swap(x->right, x->left);
        }

        x->dist = 1 + min(getDist(x->left), getDist(x->right));
        return x;
    }

    Node *push(Node *root, ll val) {
        Node *new_node = new Node(nullptr, nullptr, val);
        return merge(root, new_node);
    }

    ll top(Node *root) {
        return root->key;
    }

    Node *pop(Node *root) {
        return merge(root->left, root->right);
    }

    bool empty(Node *root) {
        return root == nullptr;
    }
}
