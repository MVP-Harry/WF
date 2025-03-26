#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#ifdef LOCAL
    #include <bits/debug.h>
#else
    #define dbg(...)
#endif

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n, m, x, y;
    cin >> n >> m >> x >> y;

    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    auto check = [&](int num) -> bool {
        // first num book shelves can only fit y books
        // remaining book shelves can fit x books
        vector<int> capacity(n);
        for (int i = 0; i < num; i++) capacity[i] = y;
        for (int i = num; i < n; i++) capacity[i] = x;

        int ptr = n - 1;
        for (int i = m - 1; i >= 0; i--) {
            if (capacity[ptr] == 0) ptr--;
            if (ptr < 0 || a[ptr] < b[i]) return false;
            capacity[ptr]--;
        }
        return true;
    };

    int l = 0, r = n, ans = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            l = mid + 1;
            ans = mid;
        } else {
            r = mid - 1;
        }
    }

    if (ans == -1) cout << "impossible\n";
    else cout << ans << "\n";

    return 0;
}
