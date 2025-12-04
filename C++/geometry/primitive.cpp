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

struct Pt {
    ll x, y;
};

Pt operator+(const Pt &a, const Pt &b) { return {a.x + b.x, a.y + b.y}; }
Pt operator-(const Pt &a, const Pt &b) { return {a.x - b.x, a.y - b.y}; }

__int128 cross128(const Pt &a, const Pt &b) { return (__int128) a.x * b.y - (__int128) a.y * b.x; }
__int128 cross128(const Pt &a, const Pt &b, const Pt &c) { return cross128(b - a, c - a); }
__int128 dot128(const Pt &a, const Pt &b) { return (__int128) a.x * b.x + (__int128) a.y * b.y; }
ll sgn128(__int128 v) { return (v > 0) - (v < 0); }

struct Line {
    Pt p;
    Pt v;
};

struct Seg {
    Pt a, b;
};

bool on_line(const Line &l, const Pt &q) {
    return sgn128(cross128(l.v, q - l.p)) == 0;
}

bool on_segment(const Seg &s, const Pt &p) {
    if (sgn128(cross128(s.a, s.b, p)) != 0) return false;
    return min(s.a.x, s.b.x) <= p.x && p.x <= max(s.a.x, s.b.x) &&
           min(s.a.y, s.b.y) <= p.y && p.y <= max(s.a.y, s.b.y);
}

ll orient(const Pt &a, const Pt &b, const Pt &c) {
    return sgn128(cross128(a, b, c));
}

bool seg_intersect(const Seg &s1, const Seg &s2) {
    Pt a = s1.a, b = s1.b, c = s2.a, d = s2.b;
    ll o1 = orient(a, b, c);
    ll o2 = orient(a, b, d);
    ll o3 = orient(c, d, a);
    ll o4 = orient(c, d, b);

    if (o1 == 0 && on_segment(s1, c)) return true;
    if (o2 == 0 && on_segment(s1, d)) return true;
    if (o3 == 0 && on_segment(s2, a)) return true;
    if (o4 == 0 && on_segment(s2, b)) return true;

    return (o1 != o2) && (o3 != o4);
}

bool line_intersection(const Line &a, const Line &b, ld &x, ld &y) {
    __int128 d = cross128(a.v, b.v);
    if (d == 0) return false;
    __int128 num = cross128(b.p - a.p, b.v);
    ld t = (ld) num / (ld) d;
    x = (ld) a.p.x + (ld) a.v.x * t;
    y = (ld) a.p.y + (ld) a.v.y * t;
    return true;
}

ld dist2_point_point(const Pt &a, const Pt &b) {
    ld dx = (ld) a.x - (ld) b.x;
    ld dy = (ld) a.y - (ld) b.y;
    return dx * dx + dy * dy;
}

ld dist2_point_line(const Line &l, const Pt &p) {
    ld A = (ld) l.v.y;
    ld B = (ld) -l.v.x;
    ld C = -A * (ld) l.p.x - B * (ld) l.p.y;
    ld num = A * (ld) p.x + B * (ld) p.y + C;
    return (num * num) / (A * A + B * B);
}

ld dist2_point_segment(const Seg &s, const Pt &p) {
    Pt ab = s.b - s.a;
    Pt ap = p - s.a;
    __int128 ab2 = dot128(ab, ab);
    if (ab2 == 0) return dist2_point_point(s.a, p);
    __int128 tnum = dot128(ap, ab);
    if (tnum <= 0) return dist2_point_point(s.a, p);
    if (tnum >= ab2) return dist2_point_point(s.b, p);
    ld t = (ld) tnum / (ld) ab2;
    ld projx = (ld) s.a.x + (ld) ab.x * t;
    ld projy = (ld) s.a.y + (ld) ab.y * t;
    ld dx = projx - (ld) p.x;
    ld dy = projy - (ld) p.y;
    return dx * dx + dy * dy;
}


__int128 twice_area128(const vector<Pt> &p) {
    ll n = p.size();
    __int128 s = 0;
    for (ll index_i = 0; index_i < n; index_i++) {
        ll index_j = (index_i + 1) % n;
        s += (__int128) p[index_i].x * p[index_j].y - (__int128) p[index_i].y * p[index_j].x;
    }
    return s;
}

ld area_polygon(const vector<Pt> &p) {
    __int128 s2 = twice_area128(p);
    if (s2 < 0) s2 = -s2;
    return (ld) s2 / 2.0L;
}

// 0 outside, 1 inside, 2 on boundary
ll point_in_polygon(const vector<Pt> &poly, const Pt &p) {
    ll n = poly.size();
    bool inside = false;
    for (ll index_i = 0; index_i < n; index_i++) {
        Pt a = poly[index_i];
        Pt b = poly[(index_i + 1) % n];

        if (on_segment(Seg{a, b}, p)) {
            return 2;
        }

        bool up = (a.y > p.y) != (b.y > p.y);
        if (up) {
            __int128 cr = cross128(a, b, p);
            if ((cr > 0) == (b.y > a.y)) {
                inside = !inside;
            }
        }
    }
    return inside ? 1 : 0;
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
