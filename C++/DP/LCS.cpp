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
#define all(x) x.begin(), x.end()
#define print(x) for (auto element : x) cout << element << " ";
#define endl "\n"

#define I_AM_OUTSIDER = true;
#define RAMAZAN_RAKHMATULLIN_FAN_CLUB = true;

// freopen("file.txt","r",stdin);
// getline(cin,string);
// num % mod = (num % mod + mod) % mod
// rand() % (end - start + 1) + start;

template<class T>
vector<ll> lcs_row_forward(const vector<T> &a, ll aL, ll aR, const vector<T> &b, ll bL, ll bR) {
    ll m = bR - bL;
    vector<ll> prev(m + 1, 0), cur(m + 1, 0);
    for (ll index = aL; index < aR; index++) {
        cur[0] = 0;
        const T &x = a[index];
        for (ll j = 1; j <= m; j++) {
            const T &y = b[bL + j - 1];
            if (x == y) {
                cur[j] = prev[j - 1] + 1;
            } else {
                cur[j] = max(prev[j], cur[j - 1]);
            }
        }
        prev.swap(cur);
    }
    return prev;
}

template<class T>
vector<ll> lcs_row_backward(const vector<T> &a, ll aL, ll aR, const vector<T> &b, ll bL, ll bR) {
    ll m = bR - bL;
    vector<ll> prev(m + 1, 0), cur(m + 1, 0);
    for (ll index = aR - 1; index >= aL; index--) {
        cur[0] = 0;
        const T &x = a[index];
        for (ll j = 1; j <= m; j++) {
            const T &y = b[bR - j];
            if (x == y) {
                cur[j] = prev[j - 1] + 1;
            } else {
                cur[j] = max(prev[j], cur[j - 1]);
            }
        }
        prev.swap(cur);
    }
    return prev;
}

template<class T>
void lcs_hirschberg(const vector<T> &a, ll aL, ll aR, const vector<T> &b, ll bL, ll bR,
                    vector<ll> &ia, vector<ll> &ib) {
    if (aL >= aR || bL >= bR) return;
    if (aR - aL == 1) {
        const T &x = a[aL];
        for (ll j = bL; j < bR; j++) {
            if (b[j] == x) {
                ia.push_back(aL);
                ib.push_back(j);
                break;
            }
        }
        return;
    }

    ll aM = (aL + aR) >> 1;
    auto L = lcs_row_forward(a, aL, aM, b, bL, bR);
    auto R = lcs_row_backward(a, aM, aR, b, bL, bR);

    ll m = bR - bL;
    ll bestK = 0, bestVal = -1;
    for (ll k = 0; k <= m; k++) {
        ll val = L[k] + R[m - k];
        if (val > bestVal) {
            bestVal = val;
            bestK = k;
        }
    }

    ll bM = bL + bestK;
    lcs_hirschberg(a, aL, aM, b, bL, bM, ia, ib);
    lcs_hirschberg(a, aM, aR, b, bM, bR, ia, ib);
}

template<class T>
pair<vector<ll>, vector<ll> > lcs(const vector<T> &a, const vector<T> &b) {
    vector<ll> ia, ib;
    lcs_hirschberg(a, 0, a.size(), b, 0, b.size(), ia, ib);
    return {ia, ib};
}

pair<vector<ll>, vector<ll> > lcs(const string &a, const string &b) {
    vector<char> va(a.begin(), a.end()), vb(b.begin(), b.end());
    return lcs(va, vb);
}

void solution() {
}

int main() {
    srand(time(nullptr));
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll t = 1;
    // cin>>t;
    while (t--) {
        solution();
    }
}
