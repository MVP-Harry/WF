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

    cout << "? " << n << " " << 1 << "\n";
    cout.flush();
    int x;
    cin >> x;

    if (x == n) {
        cout << "! " << n << " " << 1 << "\n";
    } else {
        cout << "? " << n - x << " " << 1 << "\n";
        cout.flush();
        int y;
        cin >> y;
        cout << "! " << x << " " << y << "\n";
    }
    
    return 0;
}
