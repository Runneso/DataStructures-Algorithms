#include "../linear/Deque.hpp"
#include <cassert>

int main() {
    srand(time(nullptr));

    deque<ll> dq;
    Deque deque;

    for (ll test = 0; test < 1e6; test++) {
        ll type = rand() % 4;

        switch (type) {
            case 0: {
                if (!deque.empty()) {
                    dq.pop_front();
                    deque.pop_front();
                }
                break;
            }
            case 1: {
                if (!deque.empty()) {
                    dq.pop_back();
                    deque.pop_back();
                }
                break;
            }
            case 2: {
                ll value = rand() % 1000 - 500;
                dq.push_back(value);
                deque.push_back(value);
                break;
            }
            case 3: {
                ll value = rand() % 1000 - 500;
                dq.push_front(value);
                deque.push_front(value);
                break;
            }
        }
        // assert(dq.empty() == deque.empty());
        vector<ll> values1(all(dq));
        vector<ll> values2;
        for (ll value: deque) {
            values2.push_back(value);
        }
        if (!dq.empty()) {
            assert(dq.front() == deque.get_front());
            assert(dq.back() == deque.get_back());
        }
        assert(values1 == values2);
    }

    return 0;
}
