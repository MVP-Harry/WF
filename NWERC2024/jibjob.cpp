#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#ifdef LOCAL
    #include <bits/debug.h>
#else
    #define dbg(...)
#endif

struct Tower {
    int x, y, h;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    vector<Tower> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y >> a[i].h;
    }

    for (int i = 0; i < n; i++) {
        int maxLength = a[i].h;
        for (int j = 0; j < n; j++) {
            if (a[j].h > a[i].h) {
                int d = sqrt((a[j].x - a[i].x) * (a[j].x - a[i].x) + (a[j].y - a[i].y) * (a[j].y - a[i].y));
                maxLength = min(maxLength, d);
            }
        }
        cout << maxLength << "\n";
    }
    
    return 0;
}
