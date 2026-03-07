#include "../trees/SegmentTree.hpp"
#include <cassert>

int main() {
    srand(time(nullptr));
    ll n = 100;
    vector<ll> arr(n);

    function<void(ll, ll, ll)> add_range = [&](ll l, ll r, ll value) {
        for (ll index = l; index <= r; index++) {
            arr[index] += value;
        }
    };

    function<ll(ll,ll)> max_range = [&](ll l, ll r) {
        ll res = LLONG_MIN;
        for (ll index = l; index <= r; index++) {
            res = max(res, arr[index]);
        }
        return res;
    };

    function<ll(ll,ll)> randint = [](ll l, ll r) {
        return rand() % (r - l + 1) + l;
    };

    for (ll index = 0; index < n; index++) {
        arr[index] = rand() % 1000 - 500;
    }
    SegmentTree tree(arr);


    for (ll test = 0; test < 1e6; test++) {
        ll type = rand() % 2;

        if (type == 0) {
            ll value = rand() % 1000 - 500;
            ll l = randint(0, n - 1);
            ll r = randint(l, n - 1);
            add_range(l, r, value);
            tree.add_range(l, r, value);
        } else {
            ll l = randint(0, n - 1);
            ll r = randint(l, n - 1);
            assert(max_range(l,r) == tree.max_range(l,r));
        }
    }

    return 0;
}
