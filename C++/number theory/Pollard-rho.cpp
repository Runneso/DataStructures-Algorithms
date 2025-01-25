#include <bits/stdc++.h>

using namespace std;


uint64_t modmul(const uint64_t a, const uint64_t b, const uint64_t M) {
    const int64_t ret = a * b - M * static_cast<int64_t>(1.L / M * a * b);
    return ret + M * (ret < 0) - M * (ret >= static_cast<int64_t>(M));
}

uint64_t modpow(uint64_t a, uint64_t b, uint64_t M) {
    uint64_t ret = 1;

    for (; b; a = modmul(a, a, M), b /= 2) {
        if (b & 1) ret = modmul(ret, a, M);
    }
    return ret;
}

uint64_t pollard_rho(uint64_t n) {
    auto f = [n](const uint64_t x) { return modmul(x, x, n) + 1; };
    uint64_t x = 0, y = 0, t = 30, prd = 2, i = 1, q;

    while (t++ % 40 || __gcd(prd, n) == 1) {
        if (x == y) {
            x = ++i, y = f(x);
        }
        if ((q = modmul(prd, max(x, y) - min(x, y), n))) {
            prd = q;
        }
        x = f(x), y = f(f(y));
    }
    return __gcd(prd, n);
}


vector<uint64_t> factor(uint64_t n) {
    if (n == 1) {
        return {};
    }

    if (isPrime(n)) {
        return {n};
    }
    uint64_t x = pollard_rho(n);
    auto l = factor(x), r = factor(n / x);
    l.insert(l.end(), r.begin(), r.end());
    return l;
}

vector<uint64_t> bruteFactor(uint64_t n) {
    if (n == 1) {
        return {};
    }
    vector<uint64_t> ans;

    uint64_t div = 2;
    while (div * div <= n) {
        while (n % div == 0) {
            ans.push_back(div);
            n /= div;
        }
        div++;
    }

    if (n > 1) {
        ans.push_back(n);
    }
    return ans;
}
