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

size_t var_count = 0;
set<char> all_letters;
map<char, size_t> letter_to_index;
map<char, bool> ans;


// freopen("file.txt","r",stdin);
// getline(cin,string);
// num % mod = (num % mod + mod) % mod
// rand() % (end - start + 1) + start;

string strip(const string &s) {
    size_t start = 0, end = s.size() - 1;
    const size_t n = s.size();

    while (start < n && isspace(s[start])) {
        start++;
    }

    if (start == n) {
        return {};
    }

    while (end > start && isspace(s[end])) {
        end--;
    }

    return s.substr(start, end - start + 1);
}

vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;

    for (const char c: s) {
        if (c == delimiter) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else {
            token += c;
        }
    }

    if (!token.empty()) {
        tokens.push_back(token);
        token.clear();
    }

    return tokens;
}

vector<pair<string, string> > parse(const string &s) {
    vector<string> splitted = split(strip(s), '^');
    vector<pair<string, string> > result;

    for (string &part: splitted) {
        part = part.substr(1, part.size() - 2);
        vector<string> p = split(strip(part), 'v');
        for (string &x: p) x = strip(x);
        assert(p.size() == 2);
        result.emplace_back(p.front(), p.back());
    }

    return result;
}

pair<char, bool> parse_var(string &var) {
    if (var.front() == '!') {
        return {var[1], false};
    }
    return {var[0], true};
}

void fill_id(char c) {
    if (const auto it = letter_to_index.find(c); it != letter_to_index.end()) {
        return;
    }
    const size_t new_id = var_count++;
    letter_to_index[c] = new_id;
}

size_t get_node_id(const char c, const bool is_true) {
    fill_id(c);
    const size_t base_id = letter_to_index[c] * 2;
    return is_true ? base_id : base_id + 1;
}

vector<size_t> kosoraju_scc(vector<vector<size_t> > &graph, vector<vector<size_t> > &rev_graph, size_t total_vertices) {
    vector<size_t> order;
    vector<bool> visited(total_vertices, false);
    vector<size_t> components(total_vertices);

    size_t cmp = 0;

    function<void(size_t)> dfs1 = [&](size_t u) {
        visited[u] = true;
        for (const size_t v: graph[u]) {
            if (!visited[v]) {
                dfs1(v);
            }
        }
        order.push_back(u);
    };

    for (size_t node = 0; node < total_vertices; node++) {
        if (!visited[node]) {
            dfs1(node);
        }
    }

    reverse(all(order));

    function<void(size_t)> dfs2 = [&](size_t u) {
        visited[u] = true;
        components[u] = cmp;
        for (const size_t v: rev_graph[u]) {
            if (!visited[v]) {
                dfs2(v);
            }
        }
    };

    visited.assign(total_vertices, false);

    for (const size_t u: order) {
        if (!visited[u]) {
            dfs2(u);
            cmp++;
        }
    }

    return components;
}

void solution() {
    const string s = "(!avc)^(!cv!a)^(avb)^(!bva)";
    vector<pair<string, string> > parsed = parse(s);
    for (auto [var1,var2]: parsed) {
        all_letters.insert(parse_var(var1).first);
        all_letters.insert(parse_var(var2).first);
    }

    for (const char c: all_letters) {
        fill_id(c);
    }

    const size_t total_vertices = var_count * 2;

    vector<vector<size_t> > graph(total_vertices);
    vector<vector<size_t> > rev_graph(total_vertices);


    for (auto [var1, var2]: parsed) {
        auto [c1, is_true1] = parse_var(var1);
        auto [c2, is_true2] = parse_var(var2);

        const size_t from1 = get_node_id(c1, !is_true1);
        const size_t to1 = get_node_id(c2, is_true2);
        graph[from1].push_back(to1);
        rev_graph[to1].push_back(from1);

        const size_t from2 = get_node_id(c2, !is_true2);
        const size_t to2 = get_node_id(c1, is_true1);
        graph[from2].push_back(to2);
        rev_graph[to2].push_back(from2);
    }

    vector<size_t> components = kosoraju_scc(graph, rev_graph, total_vertices);

    for (const char c: all_letters) {
        const size_t true_id = get_node_id(c, true);
        const size_t false_id = get_node_id(c, false);
        ans[c] = components[true_id] > components[false_id];
        if (components[true_id] == components[false_id]) {
            cout << "No solution" << endl;
            return;
        }
    }

    for (auto [k,v]: ans) {
        cout << k << " : " << (v ? "True" : "False") << endl;
    }
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
