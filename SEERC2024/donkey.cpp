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

    ll sum = 0;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    if (sum == 0) {
        cout << "Puss in Boots\n";
    } else {
        sum -= *max_element(a.begin(), a.end());
        cout << (sum < n ? "Donkey\n" : "Puss in Boots\n");
    }

    return 0;
}
