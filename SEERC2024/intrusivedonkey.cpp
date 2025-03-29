#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#ifdef LOCAL
    #include <bits/debug.h>
#else
    #define dbg(...)
#endif

// The ultimate lazy segment tree template
template<class Info, class Tag>
struct LazySegmentTree {
    const int n;
    vector<Info> info;
    vector<Tag> tag;
    LazySegmentTree(int _n) : n(_n), info(4 << __lg(_n)), tag(4 << __lg(_n)) {}
    LazySegmentTree(vector<Info> init) : LazySegmentTree(init.size()) {
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void apply(int p, const Tag &v) {
        info[p].apply(v);
        tag[p].apply(v);
    }
    void push(int p) {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v) {
        modify(1, 0, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        push(p);
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
    void rangeApply(int p, int l, int r, int x, int y, const Tag &v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
    void rangeApply(int l, int r, const Tag &v) {
        return rangeApply(1, 0, n, l, r, v);
    }
    int find_first(int p, int l, int r, ll val) {
        if (l == r - 1) {
            if (val <= info[p].mx) return l;
            return -1;
        }
        int mid = (l + r) / 2;
        push(p);
        if (info[p * 2].mx >= val) return find_first(p * 2, l, mid, val);
        else return find_first(p * 2 + 1, mid, r, val);
    }
};

struct Tag {
    ll add = 0;
    ll mul = 1;
    
    void apply(Tag t) {
        mul *= t.mul;
        add = add * t.mul + t.add;
    }
};

struct Info {
    ll mx = 0;
    
    void apply(Tag t) {
        mx = mx * t.mul + t.add;
    }
};

Info operator+(Info a, Info b) {
    Info c;
    c.mx = max(a.mx, b.mx);
    return c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n, q;
    string s;
    cin >> n >> q >> s;

    vector<Info> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = {i + 1};
    }
    LazySegmentTree<Info, Tag> segtree(a);

    while (q--) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            ll l, r;
            cin >> l >> r;
            int idx1 = segtree.find_first(1, 0, n, l);
            int idx2 = segtree.find_first(1, 0, n, r);
            ll rightEnd = segtree.rangeQuery(idx2, idx2 + 1).mx;
            segtree.rangeApply(idx1, idx2 + 1, {-(l - 1), 2});
            segtree.rangeApply(idx2, idx2 + 1, {r - rightEnd, 1});
            if (idx2 < n - 1) {
                segtree.rangeApply(idx2 + 1, n, {(r - l + 1), 1});
            }
        } else {
            ll idx;
            cin >> idx;
            int k = segtree.find_first(1, 0, n, idx);
            assert(k >= 0 && k < n);
            cout << s[k] << "\n";
        }
    }
    
    return 0;
}
