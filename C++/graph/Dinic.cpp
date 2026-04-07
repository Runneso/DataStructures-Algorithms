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

struct Dinic {
    struct Edge {
        ll from, to, cap, flow;
    };

    ll n, m, s, t;
    ll edge_id = 0, Q = 30;
    bool computed = false;
    vector<Edge> edges;
    vector<vector<ll> > graph;
    vector<ll> levels, ptrs;
    queue<ll> q;

    Dinic(ll n, ll m,ll s, ll t): n(n), m(m), s(s), t(t) {
        edges.resize(2 * m);
        graph.resize(n);
        levels.resize(n);
        ptrs.resize(n);
    }

    void add_edge(ll u, ll v, ll c, bool directed = true) {
        if (directed) {
            edges[edge_id] = {u, v, c, 0};
            edges[edge_id ^ 1] = {v, u, 0, 0};
            graph[u].push_back(edge_id);
            graph[v].push_back(edge_id ^ 1);
            edge_id += 2;
        } else {
            edges[edge_id] = {u, v, c, 0};
            edges[edge_id ^ 1] = {v, u, c, 0};
            graph[u].push_back(edge_id);
            graph[v].push_back(edge_id ^ 1);
            edge_id += 2;
        }
    }

    void prepare() {
        fill(all(levels), -1);
        fill(all(ptrs), 0);
        levels[s] = 0;
        q.push(s);
    }

    bool bfs(ll limit) {
        prepare();
        while (!q.empty()) {
            ll node = q.front();
            q.pop();

            for (ll edge_id: graph[node]) {
                Edge &edge = edges[edge_id];
                ll remaining = edge.cap - edge.flow;
                if (remaining == 0 || remaining < limit) {
                    continue;
                }
                if (levels[edge.to] != -1) {
                    continue;
                }
                levels[edge.to] = levels[node] + 1;
                q.push(edge.to);
            }
        }
        return levels[t] != -1;
    }

    ll dfs(ll node, ll flow, ll limit) {
        if (node == t) {
            return flow;
        }

        for (ll &ptr = ptrs[node]; ptr < graph[node].size(); ptr++) {
            Edge &edge = edges[graph[node][ptr]];
            Edge &reverse_edge = edges[graph[node][ptr] ^ 1];
            ll remaining = edge.cap - edge.flow;

            if (remaining == 0 || remaining < limit) {
                continue;
            }

            if (levels[edge.from] + 1 != levels[edge.to]) {
                continue;
            }

            ll delta = dfs(edge.to, min(flow, remaining), limit);
            if (delta > 0) {
                edge.flow += delta;
                reverse_edge.flow -= delta;
                return delta;
            }
        }

        return 0LL;
    }

    void compute() {
        for (ll limit = (1LL << Q); limit > 0; limit >>= 1) {
            while (bfs(limit)) {
                while (dfs(s, LLONG_MAX, limit)) {
                }
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

    Dinic d(n, m, 0, n - 1);

    for (ll index = 0; index < m; index++) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--, v--;
        d.add_edge(u, v, c);
    }
    d.compute();
    cout << d.max_flow() << endl;
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
