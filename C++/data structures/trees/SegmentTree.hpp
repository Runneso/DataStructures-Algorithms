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


struct SegmentTree {
    ll n;
    vector<ll> tmax, tsum;

    SegmentTree(vector<ll> &arr) {
        this->n = arr.size();
        tmax.resize(4 * n);
        tsum.resize(4 * n);
        build(0, n - 1, 0, arr);
    }

    void push(ll i) {
        if (tsum[i] != 0) {
            tmax[2 * i + 1] += tsum[i];
            tmax[2 * i + 2] += tsum[i];
            tsum[2 * i + 1] += tsum[i];
            tsum[2 * i + 2] += tsum[i];
            tsum[i] = 0;
        }
    }

    void build(ll l,ll r,ll i, vector<ll> &arr) {
        if (l == r) {
            tmax[i] = arr[l];
            return;
        }

        ll mid = (l + r) / 2;

        build(l, mid, 2 * i + 1, arr);
        build(mid + 1, r, 2 * i + 2, arr);
        tmax[i] = max(tmax[2 * i + 1], tmax[2 * i + 2]);
    }

    void add_range(ll l, ll r,ll i, ll lx,ll rx, ll value) {
        if (lx > r || rx < l) {
            return;
        }

        if (lx >= l && rx <= r) {
            tmax[i] += value;
            tsum[i] += value;
            return;
        }

        push(i);
        ll mid = (lx + rx) / 2;
        add_range(l, r, 2 * i + 1, lx, mid, value);
        add_range(l, r, 2 * i + 2, mid + 1, rx, value);
        tmax[i] = max(tmax[2 * i + 1], tmax[2 * i + 2]);
    }

    void add_range(ll l, ll r, ll value) {
        add_range(l, r, 0, 0, n - 1, value);
    }

    ll max_range(ll l, ll r, ll i, ll lx,ll rx) {
        if (lx > r || rx < l) {
            return LLONG_MIN;
        }

        if (lx >= l && rx <= r) {
            return tmax[i];
        }

        push(i);
        ll mid = (lx + rx) / 2;
        ll left = max_range(l, r, 2 * i + 1, lx, mid);
        ll right = max_range(l, r, 2 * i + 2, mid + 1, rx);
        return max(left, right);
    }

    ll max_range(ll l,ll r) {
        return max_range(l, r, 0, 0, n - 1);
    }
};
