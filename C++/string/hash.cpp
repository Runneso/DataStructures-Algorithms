#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx,avx2,avx512,fma")

#define ll long long int
#define ld long double

#define PI acos(-1)
#define inf LONG_LONG_MAX
#define MOD (1'000'000'000+7)
#define MOD_ (1'000'000'000+9)
#define BASE (911382323)
#define BASE_ (972663749)
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define print(x) for(auto element:x) cout << element << " ";
#define endl "\n"

#define I_AM_OUTSIDER = true;

struct HashString {
    ll MOD1, MOD2;
    ll base1, base2;

    vector<ll> p1, p2;
    vector<ll> h1, h2;

    HashString(const string &s, const ll base1, const ll base2, const ll MOD1, const ll MOD2): MOD1(MOD1), MOD2(MOD2),
        base1(base1), base2(base2) {
        size_t n = s.size();
        p1.resize(n + 1, 1);
        p2.resize(n + 1, 1);
        h1.resize(n + 1, 0);
        h2.resize(n + 1, 0);

        for (size_t index = 1; index <= n; index++) {
            p1[index] = (p1[index - 1] * base1) % MOD1;
            p2[index] = (p2[index - 1] * base2) % MOD2;

            char curr = s[index - 1] - 'a' + 1;
            h1[index] = (h1[index - 1] * base1 + curr) % MOD1;
            h2[index] = (h2[index - 1] * base2 + curr) % MOD2;
        }
    }

    HashString(const vector<ll> &s, const ll base1, const ll base2, const ll MOD1, const ll MOD2): MOD1(MOD1),
        MOD2(MOD2), base1(base1), base2(base2) {
        size_t n = s.size();
        p1.resize(n + 1, 1);
        p2.resize(n + 1, 1);
        h1.resize(n + 1, 0);
        h2.resize(n + 1, 0);

        for (size_t index = 1; index <= n; index++) {
            p1[index] = (p1[index - 1] * base1) % MOD1;
            p2[index] = (p2[index - 1] * base2) % MOD2;

            ll curr = s[index - 1] + 1;
            h1[index] = (h1[index - 1] * base1 + curr) % MOD1;
            h2[index] = (h2[index - 1] * base2 + curr) % MOD2;
        }
    }

    pair<ll,ll> get(ll l, ll r) {
        ll length = r - l + 1;
        ll x1 = (h1[r + 1] + MOD1 - (h1[l] * p1[length]) % MOD1) % MOD1;
        ll x2 = (h2[r + 1] + MOD2 - (h2[l] * p2[length]) % MOD2) % MOD2;
        return {x1, x2};
    }
};
