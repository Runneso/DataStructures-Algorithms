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

// freopen("file.txt","r",stdin);
// getline(cin,string);
// num % mod = (num % mod + mod) % mod
// rand() % (end - start + 1) + start;

static vector<int> sa_is(const vector<int>& s, int K) {
    int n = (int)s.size();
    if (n == 1) return {0};

    vector<bool> isS(n, false), isLMS(n, false);
    isS[n-1] = true;
    for (int i = n-2; i >= 0; --i) {
        if (s[i] < s[i+1]) isS[i] = true;
        else if (s[i] > s[i+1]) isS[i] = false;
        else isS[i] = isS[i+1];
    }
    for (int i = 1; i < n; ++i)
        isLMS[i] = isS[i] && !isS[i-1];

    auto bucket_sizes = [&](vector<int>& bsize){
        bsize.assign(K+1, 0);
        for (int x : s) ++bsize[x];
    };
    auto bucket_heads = [&](const vector<int>& bsize){
        vector<int> head(K+1);
        int sum = 0;
        for (int i = 0; i <= K; ++i) {
            head[i] = sum;
            sum += bsize[i];
        }
        return head;
    };
    auto bucket_tails = [&](const vector<int>& bsize){
        vector<int> tail(K+1);
        int sum = 0;
        for (int i = 0; i <= K; ++i) {
            sum += bsize[i];
            tail[i] = sum - 1;
        }
        return tail;
    };

    vector<int> SA(n, -1), bsize;
    bucket_sizes(bsize);

    auto induce = [&](const vector<int>& lms_pos){
        fill(SA.begin(), SA.end(), -1);
        auto tail = bucket_tails(bsize);
        for (int i = (int)lms_pos.size()-1; i >= 0; --i) {
            int p = lms_pos[i];
            SA[tail[s[p]]--] = p;
        }
        auto head = bucket_heads(bsize);
        for (int i = 0; i < n; ++i) {
            int j = SA[i]-1;
            if (j >= 0 && !isS[j]) SA[head[s[j]]++] = j;
        }
        tail = bucket_tails(bsize);
        for (int i = n-1; i >= 0; --i) {
            int j = SA[i]-1;
            if (j >= 0 && isS[j]) SA[tail[s[j]]--] = j;
        }
    };

    vector<int> lms_pos;
    lms_pos.reserve(n);
    for (int i = 1; i < n; ++i) if (isLMS[i]) lms_pos.push_back(i);

    induce(lms_pos);

    vector<int> lms_order;
    lms_order.reserve(lms_pos.size());
    for (int i = 0; i < n; ++i) if (isLMS[SA[i]]) lms_order.push_back(SA[i]);

    vector<int> name(n, -1);
    int cur_name = 0;
    name[lms_order[0]] = 0;

    auto equal_lms = [&](int a, int b){
        if (a == n || b == n) return a == b;
        int i = 0;
        while (true) {
            bool aL = isLMS[a + i], bL = isLMS[b + i];
            if (s[a+i] != s[b+i]) return false;
            if (aL != bL) return false;
            if (aL && bL && i > 0) return true;
            ++i;
        }
    };

    for (int i = 1; i < (int)lms_order.size(); ++i) {
        int a = lms_order[i-1], b = lms_order[i];
        if (!equal_lms(a, b)) ++cur_name;
        name[b] = cur_name;
    }

    vector<int> s1;
    s1.reserve(lms_pos.size());
    for (int p : lms_pos) s1.push_back(name[p]);

    vector<int> sa1;
    if (cur_name + 1 == (int)s1.size()) {
        sa1.resize(s1.size());
        for (int i = 0; i < (int)s1.size(); ++i) sa1[s1[i]] = i;
    } else {
        sa1 = sa_is(s1, cur_name);
    }

    vector<int> ordered_lms(lms_pos.size());
    for (int i = 0; i < (int)lms_pos.size(); ++i)
        ordered_lms[i] = lms_pos[sa1[i]];

    induce(ordered_lms);
    return SA;
}

vector<ll> build_suffix_array_linear(const string& s) {
    int n = (int)s.size();
    vector<int> a(n + 1);
    for (int i = 0; i < n; ++i) a[i] = (unsigned char)s[i] + 1;
    a[n] = 0;
    int K = 256;
    vector<int> SA = sa_is(a, K);
    vector<ll> res;
    res.reserve(n);
    for (int p : SA) if (p != n) res.push_back(p);
    return res;
}

vector<ll> buildSufMas(string &s) {
    s += "$";
    ll n = s.size();

    vector<pair<char,ll> > order(n);
    vector<ll> c(n);


    for (ll index = 0; index < n; index++) {
        order[index] = {s[index], index};
    }
    sort(all(order));

    for (ll index = 0, cnt = 0; index < n; index++) {
        if (index && order[index - 1].first != order[index].first) {
            cnt++;
        }
        c[order[index].second] = cnt;
    }

    vector<pair<pair<ll,ll>,ll> > t(n);

    for (ll k = 1; k < n; k <<= 1) {
        for (ll index = 0; index < n; index++) {
            t[index] = {{c[index], c[(index + k) % n]}, index};
        }
        sort(all(t));
        for (ll index = 0, cnt = 0; index < n; index++) {
            if (index && t[index - 1].first != t[index].first) {
                cnt++;
            }
            c[t[index].second] = cnt;
        }
    }

    vector<ll> p(n);

    for (ll index = 0; index < n; index++) {
        p[c[index]] = index;
    }
    p.erase(p.begin());
    s.pop_back();
    return p;
}

vector<ll> kasai(vector<ll> &sufMas, string &s) {
    ll n = s.size();
    vector<ll> lcp(n - 1, 0);
    vector<ll> r(n);

    for (ll index = 0; index < n; index++) {
        r[sufMas[index]] = index;
    }
    ll curr = 0;
    for (ll index = 0; index < n; index++) {
        ll pos = r[index];

        if (pos == n - 1) {
            curr = 0;
            continue;
        }

        ll nxt = sufMas[pos + 1];

        while (index + curr < n && nxt + curr < n && s[index + curr] == s[nxt + curr]) {
            curr++;
        }

        lcp[pos] = curr;

        curr = max(0LL, curr - 1);
    }
    return lcp;
}

void solution() {
    string s;
    cin >> s;
    vector<ll> sufMas = build_suffix_array_linear(s);
    for (ll num: sufMas) {
        cout << num + 1 << ' ';
    }
    cout << endl;
    print(kasai(sufMas, s));
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
