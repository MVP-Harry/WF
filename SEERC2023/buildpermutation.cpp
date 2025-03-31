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

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<pair<int, int>> b(n);
    for (int i = 0; i < n; i++) {
        b[i].first = a[i];
        b[i].second = i;
    }
    sort(b.begin(), b.end());
    dbg(b);

    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        p[b[i].second] = i;
    }

    vector<int> c(n), ans(n);
    for (int i = 0; i < n; i++) {
        c[i] = b[n - 1 - p[i]].first;
        ans[i] = b[n - 1 - p[i]].second;
        dbg(c[i]);
        if (i > 0 && c[i] + a[i] != c[i - 1] + a[i - 1]) {
            cout << -1 << "\n";
            return 0;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] + 1 << " \n"[i == n - 1];
    }

    return 0;
}
