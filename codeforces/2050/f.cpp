/*
 * given two numbers, how to find all m s.t. they are equal mod m?
 * take two numbers a and b
 * (a - b) mod M = ((a mod M - b mod M) + M % M)'
 */
#include <bits/stdc++.h>
using namespace std;

struct segtree {
	int n;
	vector<int> t;

	segtree(int _n) {
		n = _n;
		t.resize(4 * n, 0);
	}

	int merge(int v1, int v2) {
		return gcd(v1, v2);
	}

	void update(int v, int l, int r, int p, int val) {
		if (l + 1 == r) {
			t[v] = val;
                        return;
		}
		int m = (l + r) / 2;
		if (p < m) update(v * 2 + 1, l, m, p, val);
		else update(v * 2 + 2, m, r, p, val);
	        t[v] = gcd(t[v * 2 + 1], t[v * 2 + 2]);
        }

        int query(int v, int l, int r, int L, int R) {
                if (L >= R) {
                        return 0;
                } 
                if (l == L && r == R) {
                        return t[v];
                } 
                int m = (l + r) / 2;
                return merge(query(v * 2 + 1, l, m, L, min(m, R)),
                             query(v * 2 + 2, m, r, max(m, L), R));
        }

        void update(int p, int val) {
                update(0, 0, n, p, val);
        }

        int query(int l, int r) {
                return query(0, 0, n, l, r);
        }
};

int main() {
        cin.tie(0)->sync_with_stdio(0);
        int t; cin >> t;
        while (t--) {
		int n, q; cin >> n >> q;
		vector<int> a(n);
		for (int &x : a) cin >> x;
		vector<int> same(n); // same[i] = rightmost index where the numbers are the same
		for (int i = 0; i < n; i++) same[i] = i;

		int l = 0, r = 0;
		for (; r < n; r++) {
			if (a[l] != a[r]) { 
				while (l < r) {
					same[l] = r - 1;
					l++;
				}
			}
		}
		while (l < r) {
			same[l] = r - 1;
			l++;
		}

		segtree st(n - 1);
		for (int i = 1; i < n; i++) {
	                st.update(i - 1, abs(a[i] - a[i - 1]));
		}

                while (q--) {
                        int x, y; cin >> x >> y;
                        --x; --y;
                        // 1, 3 -> 0, 2 but we check entries 0 and 1.
                        if (x == y) {
                                cout << 0 << ' ';
                        } else {
				int res = st.query(x, y);
				cout << (same[x] >= y ? 0 : res) << ' ';
                        }
                }
                cout << '\n';
        }
}

                




		


