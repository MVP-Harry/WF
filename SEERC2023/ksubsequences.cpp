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
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        int limit = 0;
        set<pair<int, int>> s;
        for (int i = 0; i < k; i++) {
            s.insert({0, i});
        }

        for (int i = 0; i < n; i++) {
            if (a[i] == 1) {
                // first position that's lower than the limit
                auto pos = s.lower_bound({limit, 0});
                if (pos == s.begin()) {
                    limit++;
                } else {
                    pos--;
                }
                auto [x, idx] = *pos;
                cout << idx + 1 << " \n"[i == n - 1];
                s.erase(pos);
                s.insert({x + 1, idx});
            } else {
                auto [x, idx] = *s.rbegin();
                cout << idx + 1 << " \n"[i == n - 1];
                s.erase({x, idx});
                s.insert({max(0, x - 1), idx});
            }
        }
    }
    
    return 0;
}
