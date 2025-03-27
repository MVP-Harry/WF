#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#ifdef LOCAL
    #include <bits/debug.h>
#else
    #define dbg(...)
#endif

struct DSU {
    vector<int> f, siz;
    
    DSU() {}
    DSU(int n) {
        init(n);
    }
    
    void init(int n) {
        f.resize(n);
        iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }
    
    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    
    int size(int x) {
        return siz[find(x)];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> champagne(n);
    vector<int> cur(n), nxt(n);
    for (int i = 0; i < n; i++) {
        cur[i] = i;
    }

    stack<int> s;
    for (int i = n - 1; i >= 0; i--) {
        while (!s.empty()) {
            if (a[s.top()] <= a[i]) {
                s.pop();
            } else {
                break;
            }
        }
        nxt[i] = s.empty() ? n : s.top();
        s.push(i);
    }

    DSU dsu(n + 1);
    while (q--) {
        char opt;
        cin >> opt;
        if (opt == '+') {
            int l, x;
            cin >> l >> x;
            l--;
            for (int i = dsu.find(l); i != n; i = dsu.find(i)) {
                if (x + champagne[i] >= a[i]) {
                    x -= a[i] - champagne[i];
                    champagne[i] = a[i];
                    dsu.merge(nxt[i], i);
                } else {
                    champagne[i] += x;
                    break;
                }
            }
        } else {
            int l;
            cin >> l;
            cout << champagne[l - 1] << "\n";
        }
    }
    
    return 0;
}
