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

bool isPrime(const uint64_t n) {
    if (n < 2 || n % 6 % 4 != 1) {
        return (n | 1) == 3;
    }
    const uint64_t A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022}, s = __builtin_ctzll(n - 1), d = n >> s;

    for (const uint64_t a: A) {
        uint64_t p = modpow(a % n, d, n), i = s;

        while (p != 1 && p != n - 1 && a % n && i--) {
            p = modmul(p, p, n);
        }

        if (p != n - 1 && i != s) {
            return false;
        }
    }
    return true;
}

bool bruteIsPrime(const uint64_t n) {
    uint64_t div = 2;

    while (div * div <= n) {
        if (n % div == 0) {
            return false;
        }
        div++;
    }
    return true;
}
