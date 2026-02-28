/**
 * Author: Wookyung Jeong
 * Date: 2026-02-28
 * License: CC0
 * Source: folklore
 * Description: Convex hull trick for DP with monotone slopes and queries.
 *  Add lines $kx+m$ with non-increasing $k$, query minimum for non-decreasing $x$.
 *  Uses floating-point intersections.
 * Time: O(1) amortized per operation
 * Usage: LineHullDP cht; cht.add(k, m); ll ans = cht.query(x);
 * Status: stress-tested
 */
#pragma once

struct LineHullDP {
	struct Line {
		ll k, m;
		long double p;
		ll eval(ll x) const { return k * x + m; }
	};
	deque<Line> q;
	long double isect(const Line& a, const Line& b) {
		return (long double)(b.m - a.m) / (a.k - b.k);
	}
	void add(ll k, ll m) { // k must be non-increasing
		Line l{k, m, -1/.0L};
		while (!q.empty() && q.back().k == k) {
			if (q.back().m <= m) return;
			q.pop_back();
		}
		while (!q.empty()) {
			l.p = isect(q.back(), l);
			if (l.p <= q.back().p) q.pop_back();
			else break;
		}
		if (q.empty()) l.p = -1/.0L;
		q.push_back(l);
	}
	ll query(ll x) { // x must be non-decreasing
		assert(!q.empty());
		while (sz(q) > 1 && q[1].p <= (long double)x) q.pop_front();
		return q.front().eval(x);
	}
};
