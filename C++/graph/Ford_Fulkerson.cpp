#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#pragma GCC optimize("Ofast,unroll-loops")

#define ll long long int
#define ld long double
#define cd complex<ld>

template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template<class T>
struct ordered_multiset {
    ordered_set<pair<T, ll> > t;
    ll timer = 0;

    void insert(const T &x) {
        t.insert({x, timer++});
    }

    void extract(const T &x) {
        auto it = t.lower_bound({x, -1});
        if (it != t.end() && it->first == x) {
            t.erase(it);
        }
    }

    ll count_less(const T &x) const {
        return t.order_of_key({x, -1});
    }

    ll count_less_or_equal(const T &x) const {
        return t.order_of_key({x, LLONG_MAX});
    }

    T kth(ll k) const {
        return t.find_by_order(k)->first;
    }

    ll size() const {
        return (ll) t.size();
    }

    bool empty() const {
        return t.empty();
    }
};

const ld PI = acos(-1);
const ll MOD = 1'000'000'007LL;
const ll MOD_ = 1'000'000'009LL;
const ll BASE = 911382323LL;
const ll BASE_ = 972663749LL;
const ld EPS = 1e-9;

#define all(x) (x).begin(), (x).end()
#define print(x, a) for (auto element : x) cout << element + a << " ";
#define endl "\n"

#define I_AM_OUTSIDER = true;
#define RAMAZAN_RAKHMATULLIN_FAN_CLUB = true;

#ifdef LOCAL
#define debug(x) cerr << #x << " = " << (x) << endl;
#else
#define debug(x)
#endif

template<class T>
vector<T> compress(vector<T> v) {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    return v;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll randint(const ll l, const ll r) {
    return rng() % (r - l + 1) + l;
}

ll binpow(const ll a, const ll p, const ll m) {
    if (p == 0) {
        return 1;
    }
    if (p & 1) {
        return (binpow(a, p - 1, m) * a) % m;
    }
    const ll res = binpow(a, p / 2, m);
    return (res * res) % m;
}

struct Ford_Fulkerson {
    struct Edge {
        ll from, to, cap, flow;
    };

    ll n, m, s, t;
    ll edge_id = 0;
    bool computed = false;
    vector<Edge> edges;
    vector<vector<ll> > graph;

    Ford_Fulkerson(ll n, ll m, ll s, ll t) : n(n), m(m), s(s), t(t) {
        edges.resize(2 * m);
        graph.resize(n);
    }

    void add_edge(ll u, ll v, ll cap, bool directed = true) {
        if (directed) {
            edges[edge_id] = {u, v, cap, 0};
            edges[edge_id ^ 1] = {v, u, 0, 0};
            graph[u].push_back(edge_id);
            graph[v].push_back(edge_id ^ 1);
            edge_id += 2;
        } else {
            edges[edge_id] = {u, v, cap, 0};
            edges[edge_id ^ 1] = {v, u, cap, 0};
            graph[u].push_back(edge_id);
            graph[v].push_back(edge_id ^ 1);
            edge_id += 2;
        }
    }

    void compute() {
        vector<bool> visited(n, false);
        function<ll(ll,ll)> dfs = [&](ll node, ll flow) {
            if (node == t) {
                return flow;
            }
            visited[node] = true;
            for (ll edge_id: graph[node]) {
                Edge &edge = edges[edge_id];
                Edge &reverse_edge = edges[edge_id ^ 1];
                if (visited[edge.to]) {
                    continue;
                }
                if (edge.cap - edge.flow > 0) {
                    ll delta = dfs(edge.to, min(flow, edge.cap - edge.flow));
                    if (delta > 0) {
                        edge.flow += delta;
                        reverse_edge.flow -= delta;
                        return delta;
                    }
                }
            }
            return 0LL;
        };

        while (true) {
            fill(all(visited), false);
            ll delta = dfs(s, LLONG_MAX);
            if (delta == 0) {
                break;
            }
        }

        computed = true;
    }

    ll max_flow() {
        assert(computed);

        ll flow = 0;
        for (ll edge_id: graph[s]) {
            flow += edges[edge_id].flow;
        }
        return flow;
    }

    vector<ll> min_cut() {
        assert(computed);

        vector<bool> visited(n);
        vector<ll> cut;

        function<void(ll)> dfs_cut = [&](ll node) {
            visited[node] = true;
            for (ll edge_id: graph[node]) {
                Edge &edge = edges[edge_id];
                if (!visited[edge.to] && edge.flow < edge.cap) {
                    dfs_cut(edge.to);
                }
            }
        };

        dfs_cut(s);

        for (ll index = 0; index < 2 * m; index += 2) {
            Edge &edge = edges[index];
            if (visited[edge.from] != visited[edge.to]) {
                cut.push_back(index);
            }
        }
        return cut;
    }
};

void solution() {
    ll n, m;
    cin >> n >> m;

    Ford_Fulkerson ff(n, m, 0, n - 1);

    for (ll index = 0; index < m; index++) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--, v--;
        ff.add_edge(u, v, c);
    }
    ff.compute();
    cout << ff.max_flow() << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll t = 1;
    // cin >> t;
    while (t--) {
        solution();
    }
}
