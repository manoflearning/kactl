/**
 * Author: Wookyung Jeong
 * Date: 2026-02-28
 * License: CC0
 * Source: folklore
 * Description: Persistent segment tree for point updates and range sums.
 * Versions are represented by root indices.
 * Also supports order statistics on frequency trees between two versions.
 * Time: O(\log N) per update/query.
 * Usage: PST tr(n); int v = tr.add(0, p, x);
 * Status: stress-tested
 */
#pragma once

struct PST {
	struct Node {
		int l = 0, r = 0;
		ll val = 0;
	};
	vector<Node> st{Node()};
	int n;
	PST(int n) : n(n) {}
	Node& node(int i) { return st[(size_t)i]; }
	const Node& node(int i) const { return st[(size_t)i]; }
	int add(int i, int p, ll v, int l, int r) {
		int u = sz(st);
		st.push_back(node(i));
		if (l + 1 == r) {
			node(u).val += v;
			return u;
		}
		int m = (l + r) / 2;
		if (p < m) node(u).l = add(node(u).l, p, v, l, m);
		else node(u).r = add(node(u).r, p, v, m, r);
		node(u).val = node(node(u).l).val + node(node(u).r).val;
		return u;
	}
	int add(int i, int p, ll v) { return add(i, p, v, 0, n); }
	ll query(int i, int ql, int qr, int l, int r) {
		if (!i || qr <= l || r <= ql) return 0;
		if (ql <= l && r <= qr) return node(i).val;
		int m = (l + r) / 2;
		return query(node(i).l, ql, qr, l, m) + query(node(i).r, ql, qr, m, r);
	}
	ll query(int i, int l, int r) { return query(i, l, r, 0, n); }
	int kth(int a, int b, ll k, int l, int r) {
		if (l + 1 == r) return l;
		int m = (l + r) / 2;
		ll left = node(node(b).l).val - node(node(a).l).val;
		if (k < left) return kth(node(a).l, node(b).l, k, l, m);
		return kth(node(a).r, node(b).r, k - left, m, r);
	}
	int kth(int a, int b, ll k) { return kth(a, b, k, 0, n); }
};
