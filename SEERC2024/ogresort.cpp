#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#ifdef LOCAL
    #include <bits/debug.h>
#else
    #define dbg(...)
#endif

template <typename T>
struct FenwickTree {
    int n;
    vector<T> t;

    FenwickTree(int _n) {
        n = _n;
        t = vector<T>(_n + 1);
    }

    int lowbit(int x) {
        return x & -x;
    }

    void update(int x, T c) {
        assert(x >= 1);
        while (x <= n) {
            t[x] += c;
            x += lowbit(x);
        }
    }

    T query(int x) {
        if (x == 0) return 0;
        T ans = 0;
        while (x) {
            ans += t[x];
            x -= lowbit(x);
        }
        return ans;
    }

    T query(int l, int r) {
        return query(r) - query(l - 1);
    }

    // one indexed k
    T find_kth(int k) {
        assert(k >= 0);
        if (k == 0) return 0;
        int pos = 0;
        int sum = 0;
        for (int i = __lg(n); i >= 0; i--) {
            int next_pos = pos + (1 << i);
            if (next_pos <= n && sum + t[next_pos] < k) {
                sum += t[next_pos];
                pos = next_pos;
            }
        }
        return pos + 1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;

    vector<int> a(n), pos(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i] - 1] = i;
    }

    int cur = n, largest = -1;
    for (int i = n - 1; i >= 0; i--) {
        if (pos[i] > cur) {
            largest = i;
            break;
        } else {
            cur = pos[i];
        }
    }

    FenwickTree<int> fenwick(n);

    cout << largest + 1 << " " << largest + 1 << "\n";
    for (int i = largest; i >= 0; i--) {
        cout << pos[i] + 1 + (largest - i - fenwick.query(pos[i])) << " " << 1 << "\n";
        fenwick.update(pos[i] + 1, 1);
    }

    return 0;
}
