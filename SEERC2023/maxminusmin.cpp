#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#ifdef LOCAL
    #include <bits/debug.h>
#else
    #define dbg(...)
#endif

#define sz(a) (int) a.size()

template<class T>
struct MaxRMQ {
	vector<vector<T>> jmp;
	MaxRMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			for (int j = 0; j < sz(jmp[k]); j++) {
				jmp[k][j] = max(jmp[k - 1][j], jmp[k - 1][j + pw]);
            }
		}
	}
	T query(int a, int b) {
        assert(a < b);
		int dep = 31 - __builtin_clz(b - a);
		return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

template<class T>
struct MinRMQ {
	vector<vector<T>> jmp;
	MinRMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			for (int j = 0; j < sz(jmp[k]); j++) {
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
            }
		}
	}
	T query(int a, int b) {
        assert(a < b);
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        MaxRMQ maxRMQ(a);
        MinRMQ minRMQ(a);

        auto query = [&](int i, int mid) -> pair<int, int> {
            int d1 = 0;
            if (mid >= i) {
                d1 = maxRMQ.query(i, mid + 1) - minRMQ.query(i, mid + 1);;
            }
            int d2 = 0;
            int maxRest = 0, minRest = 1e9;
            if (i > 0) {
                maxRest = max(maxRest, maxRMQ.query(0, i));
                minRest = min(minRest, minRMQ.query(0, i));
            }
            if (mid < n - 1) {
                maxRest = max(maxRest, maxRMQ.query(mid + 1, n));
                minRest = min(minRest, minRMQ.query(mid + 1, n));
            }
            /*dbg(maxRest ,minRest);*/
            d2 = max(d2, maxRest - minRest);
            return {d1, d2};
        };

        /*dbg(query(0, -1));*/
        /*dbg(query(0, 0));*/

        int ans = 1e9;
        for (int i = 0; i < n; i++) {
            int l = i, r = n - 1;
            int idx = n - 1;
            while (l <= r) {
                int mid = (l + r) / 2;
                auto [d1, d2] = query(i, mid);
                if (d1 < d2) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                    idx = mid;
                }
            }
            auto [d1, d2] = query(i, idx);
            ans = min(ans, max(d1, d2));
            auto [d3, d4] = query(i, idx - 1);
            ans = min(ans, max(d3, d4));
        }
        cout << ans << "\n";
    }
    
    return 0;
}
