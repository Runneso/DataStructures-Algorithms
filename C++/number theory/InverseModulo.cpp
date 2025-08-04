#include <bits/stdc++.h>

using namespace std;


int64_t binpow(int64_t a, int64_t n, int64_t M) {
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return a;
    }
    if (n % 2 == 0) {
        int64_t result = binpow(a, n / 2, M);
        return (result * result) % M;
    }
    return (a * binpow(a, n - 1, M)) % M;
}

int64_t phi(int64_t n) {
    int64_t result = n;

    for (int64_t div = 2; div * div <= n; div++) {
        if (n % div == 0) {
            while (n % div == 0) {
                n /= div; // выкидываем все степени div
            }
            result -= result / div; // эквивалент умножению на (1 - 1/div)
        }
    }

    if (n > 1) {
        result -= result / n;
    }
    return result;
}

int64_t egcd(int64_t a, int64_t b, int64_t &x, int64_t &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int64_t x1, y1;
    int64_t d = egcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return d;
}

int64_t inverse(int64_t a, int64_t M) {
    // теорема Эйлера и малая теорема Ферма в простом модуле
    if (isPrime(M)) {
        return binpow(a, M - 2, M);
    }
    int64_t pow = phi(M);
    return binpow(a, pow - 1, M);
}


// int main() {
//     for (int64_t M = 2; M <= 1000; M++) {
//         for (int64_t a = 0; a <= 1000; a++) {
//             int64_t x, y;
//             if (egcd(a, M, x, y) != 1) {
//                 // нет обратного
//                 continue;
//             }
//             int64_t inv1 = (inverse(a, M) + M) % M;
//             int64_t inv2 = (x + M) % M;
//             assert(inv1 == inv2);
//             assert((a*inv1+M)%M == 1);
//             assert((a*inv2+M)%M == 1);
//         }
//     }
// }
