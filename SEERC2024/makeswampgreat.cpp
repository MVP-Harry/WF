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
    vector<vector<int>> pos(1e5 + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }

    vector<int> ans(n);
    for (int i = 1; i <= 100000; i++) {
        int flag = 1;
        for (int x : pos[i]) {
            int mx = max({a[x], a[(x + n - 1) % n], a[(x + 1) % n]});
            int mn = min({a[x], a[(x + n - 1) % n], a[(x + 1) % n]});
            if (a[x] == mx || a[x] == mn) {
                flag = 0;
                break;
            }
            mx = max({a[x], a[(x + 2) % n], a[(x + 1) % n]});
            mn = min({a[x], a[(x + 2) % n], a[(x + 1) % n]});
            if (a[x] == mx || a[x] == mn) {
                flag = 0;
                break;
            }
            mx = max({a[x], a[(x + n - 2) % n], a[(x + n - 1) % n]});
            mn = min({a[x], a[(x + n - 2) % n], a[(x + n - 1) % n]});
            if (a[x] == mx || a[x] == mn) {
                flag = 0;
                break;
            }
        }
        for (int x : pos[i]) {
            ans[x] = n - pos[i].size() + flag;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " \n"[i == n - 1];
    }
    
    return 0;
}
