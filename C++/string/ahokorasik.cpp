#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx,avx2,avx512,fma")

#define ll long long
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

// freopen("file.txt","r",stdin);
// getline(cin,string);
// num % mod = (num % mod + mod) % mod
// rand() % (end - start + 1) + start;


struct AhoKorasik {
    static constexpr char START = 'a', END = 'z';

    struct Node {
        Node *parent;
        Node *link;
        unordered_map<char, Node *> move;
        unordered_map<char, Node *> go;
        vector<ll> out;

        explicit Node(Node *parent = nullptr) : parent(parent), link(nullptr) {
        }
    };

    Node *root;
    stack<Node *> st;

    AhoKorasik() {
        root = new Node();
        st.push(root);
    }

    void addString(const string &s, ll idx) const {
        Node *v = root;
        for (const char &c: s) {
            if (!v->move.count(c)) {
                v->move[c] = new Node(v);
            }
            v = v->move[c];
        }
        v->out.push_back(idx);
    }

    void build() const {
        root->link = root;
        queue<Node *> q;

        for (char c = START; c <= END; c++) {
            if (root->move.count(c)) {
                Node *nxt = root->move[c];
                nxt->link = root;
                root->go[c] = nxt;
                q.push(nxt);
            } else {
                root->go[c] = root;
            }
        }

        while (!q.empty()) {
            Node *curr = q.front();
            q.pop();

            for (char c = START; c <= END; c++) {
                if (curr->move.count(c)) {
                    Node *nxt = curr->move[c];
                    nxt->link = curr->link->go[c];
                    nxt->out.insert(nxt->out.end(), all(nxt->link->out));
                    curr->go[c] = nxt;
                    q.push(nxt);
                } else {
                    curr->go[c] = curr->link->go[c];
                }
            }
        }
    }

    vector<pair<ll,ll> > findAll(const string &s) {
        vector<pair<ll,ll> > result;
        Node *v = root;
        ll n = s.size();
        for (ll index = 0; index < n; index++) {
            char c = s[index];
            v = step_forward(v, c);
            for (ll idx: v->out) {
                result.push_back({idx, index});
            }
        }
        return result;
    }

    Node *step_forward(Node *curr, char c) {
        Node *new_curr = curr->go[c];
        st.push(new_curr);
        return new_curr;
    }

    Node *step_back() {
        st.pop();
        return st.top();
    }
};
