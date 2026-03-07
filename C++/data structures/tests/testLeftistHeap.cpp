#include "../heaps/LeftistHeap.hpp"
#include <cassert>

int main() {
    srand(time(nullptr));
    leftistHeap::Node *root = nullptr;
    priority_queue<ll, vector<ll>, greater<> > pq;

    for (ll index = 0; index < 100; index++) {
        ll value = rand() % 1000 - 500;
        root = leftistHeap::push(root, value);
        pq.push(value);
        assert(leftistHeap::top(root) == pq.top());
    }

    while (!pq.empty()) {
        assert(leftistHeap::top(root) == pq.top());
        root = leftistHeap::pop(root);
        pq.pop();
    }

    for (ll index = 0; index < 100; index++) {
        for (ll index = 0; index < 100; index++) {
            ll value = rand() % 1000 - 500;
            root = leftistHeap::push(root, value);
            pq.push(value);
            assert(leftistHeap::top(root) == pq.top());
        }
        pq.pop();
        root = leftistHeap::pop(root);
    }

    return 0;
}
