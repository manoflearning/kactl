#include "../utilities/template.h"

#include "../../content/data-structures/SegmentTree2d.h"

ll brute(const vector<vector<ll>>& a, int xl, int xr, int yl, int yr) {
	ll s = 0;
	rep(i,xl,xr) rep(j,yl,yr) s += a[(size_t)i][(size_t)j];
	return s;
}

int main() {
	rep(n,1,9) rep(m,1,9) {
		Tree2D tr(n);
		vector<vector<ll>> a(n, vector<ll>(m));
		vector<pii> pts;
		rep(i,0,n) rep(j,0,m) if (rand() % 3 == 0)
			pts.push_back({i, j});
		if (pts.empty()) pts.push_back({rand() % n, rand() % m});
		for (auto [x, y] : pts) tr.fakeUpdate(x, y);
		tr.init();
		rep(it,0,4000) {
			if (rand() % 3) {
				auto [x, y] = pts[(size_t)(rand() % sz(pts))];
				ll v = rand() % 2001 - 1000;
				tr.update(x, y, v);
				a[(size_t)x][(size_t)y] = v;
			} else {
				int xl = rand() % (n + 1), xr = rand() % (n + 1);
				int yl = rand() % (m + 1), yr = rand() % (m + 1);
				if (xl > xr) swap(xl, xr);
				if (yl > yr) swap(yl, yr);
				assert(tr.query(xl, xr, yl, yr) == brute(a, xl, xr, yl, yr));
			}
		}
		rep(xl,0,n+1) rep(xr,xl,n+1) rep(yl,0,m+1) rep(yr,yl,m+1) {
			assert(tr.query(xl, xr, yl, yr) == brute(a, xl, xr, yl, yr));
		}
	}
	cout << "Tests passed!" << endl;
}
