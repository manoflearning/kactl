/**
 * Author: Wookyung Jeong
 * Date: 2026-03-03
 * License: CC0
 * Source: folklore
 * Description: Point assignments and rectangle queries on [x1, x2) x [y1, y2).
 *  Call fakeUpdate() before init(). f must be commutative.
 * Time: O(\log^2 N)
 * Status: stress-tested
 */
#pragma once

struct Tree2D {
	typedef ll T;
	static constexpr T unit = 0;
	T f(T a, T b) { return a + b; } // (any commutative associative fn)
	int n; vector<vi> ys; vector<vector<T>> st; unordered_map<ll, T> cur;
	Tree2D(int n = 0) : n(n), ys(2 * n), st(2 * n) {}
	void fakeUpdate(int x, int y) { for (x += n; x; x /= 2) ys[x].push_back(y); }
	void init() {
		for (int i = 1; i < 2 * n; i++) {
			auto& v = ys[i];
			sort(all(v));
			v.erase(unique(all(v)), v.end());
			st[i].assign(2 * sz(v), unit);
		}
	}
	int ind(int x, int y) { return (int)(lower_bound(all(ys[x]), y) - ys[x].begin()); }
	void add(int x, int y, T dif) {
		int i = ind(x, y) + sz(ys[x]);
		for (st[x][i] += dif; i /= 2;)
			st[x][i] = f(st[x][i * 2], st[x][i * 2 + 1]);
	}
	void update(int x, int y, T v) {
		ll key = ((ll)x << 32) ^ (unsigned)y;
		T dif = v - cur[key];
		if (!dif) return; cur[key] = v;
		for (x += n; x; x /= 2) add(x, y, dif);
	}
	T queryNode(int x, int yl, int yr) {
		if (ys[x].empty()) return unit;
		int b = (int)(lower_bound(all(ys[x]), yl) - ys[x].begin());
		int e = (int)(lower_bound(all(ys[x]), yr) - ys[x].begin());
		T ra = unit, rb = unit;
		for (b += sz(ys[x]), e += sz(ys[x]); b < e; b /= 2, e /= 2) {
			if (b & 1) ra = f(ra, st[x][b++]);
			if (e & 1) rb = f(st[x][--e], rb);
		}
		return f(ra, rb);
	}
	T query(int xl, int xr, int yl, int yr) {
		T ra = unit, rb = unit;
		for (xl += n, xr += n; xl < xr; xl /= 2, xr /= 2) {
			if (xl & 1) ra = f(ra, queryNode(xl++, yl, yr));
			if (xr & 1) rb = f(queryNode(--xr, yl, yr), rb);
		}
		return f(ra, rb);
	}
};
