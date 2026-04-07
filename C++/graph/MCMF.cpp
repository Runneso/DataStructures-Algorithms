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


struct MCMF {
    struct Edge {
        ll from, to, cap, cost;
    };

    ll n, m, s, t;
    ll edge_id = 0;
    vector<Edge> edges;
    vector<vector<ll> > graph;
    vector<ll> potential, dist;
    vector<ll> parent_node, parent_edge;

    MCMF(ll n, ll m,ll s,ll t): n(n), m(m), s(s), t(t) {
        edges.resize(4 * m);
        graph.resize(n);
        potential.resize(n);
        dist.resize(n);
        parent_node.resize(n);
        parent_edge.resize(n);
    }

    void add_edge(ll u,ll v, ll cap, ll cost, bool directed = true) {
        if (directed) {
            add_directed_edge(u, v, cap, cost);
        } else {
            add_directed_edge(u, v, cap, cost);
            add_directed_edge(v, u, cap, cost);
        }
    }

    void add_directed_edge(ll u, ll v, ll cap, ll cost) {
        edges[edge_id] = {u, v, cap, cost};
        edges[edge_id ^ 1] = {v, u, 0, -cost};
        graph[u].push_back(edge_id);
        graph[v].push_back(edge_id ^ 1);
        edge_id += 2;
    }

    void bellman_ford(ll s) {
        fill(potential.begin(), potential.end(), LLONG_MAX);
        potential[s] = 0;

        bool changed = true;
        for (ll iteration = 0; iteration < n - 1 && changed; iteration++) {
            changed = false;
            for (ll node = 0; node < n; node++) {
                if (potential[node] == LLONG_MAX) {
                    continue;
                }
                for (ll id: graph[node]) {
                    Edge &edge = edges[id];
                    if (edge.cap <= 0) {
                        continue;
                    }
                    if (potential[edge.to] > potential[node] + edge.cost) {
                        potential[edge.to] = potential[node] + edge.cost;
                        changed = true;
                    }
                }
            }
        }

        for (ll index = 0; index < n; index++) {
            if (potential[index] == LLONG_MAX) {
                potential[index] = 0;
            }
        }
    }

    bool dijkstra() {
        fill(dist.begin(), dist.end(), LLONG_MAX);
        fill(parent_node.begin(), parent_node.end(), -1);
        fill(parent_edge.begin(), parent_edge.end(), -1);

        priority_queue<pair<ll,ll>, vector<pair<ll,ll> >, greater<> > pq;
        dist[s] = 0;
        pq.push({0, s});

        while (!pq.empty()) {
            auto [path, node] = pq.top();
            pq.pop();
            if (path != dist[node]) {
                continue;
            }

            for (ll id: graph[node]) {
                Edge &edge = edges[id];
                if (edge.cap <= 0) {
                    continue;
                }

                ll weight = edge.cost + potential[node] - potential[edge.to];
                if (dist[edge.to] > dist[node] + weight) {
                    dist[edge.to] = dist[node] + weight;
                    parent_node[edge.to] = node;
                    parent_edge[edge.to] = id;
                    pq.push({dist[edge.to], edge.to});
                }
            }
        }

        return dist[t] != LLONG_MAX;
    }

    bool dijkstra_without_heap() {
        fill(dist.begin(), dist.end(), LLONG_MAX);
        vector<bool> used(n, false);
        fill(parent_node.begin(), parent_node.end(), -1);
        fill(parent_edge.begin(), parent_edge.end(), -1);

        dist[s] = 0;

        for (ll index = 0; index < n; index++) {
            ll to_find = -1;
            for (ll node = 0; node < n; node++) {
                if (!used[node] && (to_find == -1 || dist[node] < dist[to_find])) {
                    to_find = node;
                }
            }

            if (to_find == -1 || dist[to_find] == LLONG_MAX) {
                break;
            }

            used[to_find] = true;

            for (ll id: graph[to_find]) {
                Edge &edge = edges[id];
                if (edge.cap <= 0) {
                    continue;
                }

                ll weight = edge.cost + potential[to_find] - potential[edge.to];
                if (dist[edge.to] > dist[to_find] + weight) {
                    dist[edge.to] = dist[to_find] + weight;
                    parent_node[edge.to] = to_find;
                    parent_edge[edge.to] = id;
                }
            }
        }

        return dist[t] != LLONG_MAX;
    }

    pair<ll,ll> min_cost_max_flow() {
        bellman_ford(s);

        ll flow = 0;
        ll cost = 0;

        while (dijkstra_without_heap()) {
            for (ll node = 0; node < n; node++) {
                if (dist[node] != LLONG_MAX) {
                    potential[node] += dist[node];
                }
            }

            ll delta = LLONG_MAX;
            for (ll node = t; node != s; node = parent_node[node]) {
                Edge &edge = edges[parent_edge[node]];
                delta = min(delta, edge.cap);
            }

            for (ll node = t; node != s; node = parent_node[node]) {
                Edge &edge = edges[parent_edge[node]];
                Edge &reverse_edge = edges[parent_edge[node] ^ 1];
                edge.cap -= delta;
                reverse_edge.cap += delta;
                cost += delta * edge.cost;
            }

            flow += delta;
        }

        return {flow, cost};
    }
};

void solution() {
    ll n, m;
    cin >> n >> m;

    MCMF mcmf(n, m, 0, n - 1);

    for (ll index = 0; index < m; index++) {
        ll u, v, cap, cost;
        cin >> u >> v >> cap >> cost;
        u--, v--;
        mcmf.add_edge(u, v, cap, cost);
    }

    cout << mcmf.min_cost_max_flow().second << endl;
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
