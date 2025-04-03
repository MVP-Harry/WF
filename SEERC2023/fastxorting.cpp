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
    ll n;
    vector<T> t;

    FenwickTree(ll _n) {
        n = _n;
        t = vector<T>(_n + 1);
    }

    ll lowbit(ll x) {
        return x & -x;
    }

    void update(ll x, T c) {
        assert(x >= 1);
        while (x <= n) {
            t[x] += c;
            x += lowbit(x);
        }
    }

    T query(ll x) {
        if (x == 0) return 0;
        T ans = 0;
        while (x) {
            ans += t[x];
            x -= lowbit(x);
        }
        return ans;
    }

    T query(ll l, ll r) {
        return query(r) - query(l - 1);
    }

    // one indexed k
    T find_kth(ll k) {
        assert(k >= 0);
        if (k == 0) return 0;
        ll pos = 0;
        ll sum = 0;
        for (ll i = __lg(n); i >= 0; i--) {
            ll next_pos = pos + (1 << i);
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
    vector<int> a(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    ll k = 0;
    for (ll i = 18; i >= 0; i--) {
        if ((n >> i) & 1) {
            k = i;
            break;
        }
    }

    auto countInversions = [](vector<int> a) -> ll {
        int n = a.size();
        ll ans = 0;
        FenwickTree<int> fenwick(n);
        for (int i = 0; i < n; i++) {
            ans += i - fenwick.query(a[i]);
            fenwick.update(a[i] + 1, 1);
        }
        return ans;
    };

    ll origInversions = countInversions(a);
    int bestX = 0;
    for (int i = k - 1; i >= 0; i--) {
        auto tmp = a;
        for (int j = 0; j < n; j++) {
            tmp[j] ^= (1 << i);
        }
        ll updatedInversions = countInversions(tmp);
        if (updatedInversions < origInversions) {
            bestX += (1 << i);
        }
    }

    for (int i = 0; i < n; i++) {
        a[i] ^= bestX;
    }
    ll numInversions = countInversions(a);
    cout << numInversions + (bestX != 0) << "\n";
    
    return 0;
}
