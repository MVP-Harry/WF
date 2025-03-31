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
        int n;
        cin >> n;
        vector<int> a(2 * n);
        for (int i = 0; i < 2 * n; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        ll sum = 0;
        for (int i = 0; i < n; i++) {
            sum -= a[i];
        }
        for (int i = n; i < 2 * n; i++) {
            sum += a[i];
        }
        cout << sum << "\n";
    }
    
    return 0;
}
