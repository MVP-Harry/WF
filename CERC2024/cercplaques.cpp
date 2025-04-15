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

    vector<pair<string, string>> ans;
    unordered_map<string, vector<string>> mp;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        string name = s.substr(0, 4);
        mp[name].push_back(s);
    }

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        string name = s.substr(0, 4);
        if (mp[name].empty()) {
            cout << "NO\n";
            return 0;
        }
        ans.push_back({mp[name].back(), s});
        mp[name].pop_back();
    }

    cout << "YES\n";
    for (auto [x, y] : ans) {
        cout << x << " " << y << "\n";
    }
    
    return 0;
}
