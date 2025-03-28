#include <algorithm>
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

    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n * m);
        vector<vector<int>> cols(m);
        for (int i = 0; i < n * m; i++) {
            cin >> a[i];
            cols[i % m].push_back(a[i]);
        }

        multiset<int> s;
        for (int x : cols[m - 1]) {
            s.insert(x);
        }

        dbg(cols);
        for (int i = m - 2; i >= 0; i--) {
            sort(cols[i].begin(), cols[i].end());

            int k = -1;
            for (int j = n - 1; j >= 0; j--) {
                auto pos = s.lower_bound(cols[i][j]);
                if (pos == s.begin()) {
                    k = j;
                    break;
                } else {
                    s.erase(prev(pos));
                    if (s.empty()) {
                        break;
                    }
                }
            }

            if (s.empty()) {
                break;
            }

            for (int j = 0; j <= k; j++) {
                assert(!s.empty());
                int x = *s.rbegin();
                if (x > cols[i][j]) {
                    s.erase(prev(s.end()));
                    s.insert(cols[i][j]);
                } else {
                    break;
                }
            }
        }
        cout << (s.empty() ? "YES\n" : "NO\n");
    }
    
    return 0;
}
