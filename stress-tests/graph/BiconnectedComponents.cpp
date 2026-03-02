#include "../utilities/template.h"

#include "../../content/graph/BiconnectedComponents.h"

int compCount(int banV = -1, int banE = -1) {
	int n = sz(ed), cc = 0;
	vi seen(n);
	rep(i,0,n) if (i != banV && !seen[i]) {
		cc++;
		vector<int> q = {i};
		seen[i] = 1;
		rep(it,0,sz(q)) {
			int x = q[it];
			for (auto [y, e] : ed[x]) if (e != banE && y != banV && !seen[y]) {
				seen[y] = 1;
				q.push_back(y);
			}
		}
	}
	return cc;
}

void testCase() {
	int n = sz(ed), m = 0;
	for (auto& v : ed) for (auto [_, e] : v) m = max(m, e + 1);

	vi bridge(m), seen(m), cut(n);
	int base = compCount();
	rep(e,0,m) bridge[e] = compCount(-1, e) > base;
	rep(v,0,n) cut[v] = compCount(v) > base;

	vector<vi> comps;
	bicomps([&](const vi& c) { comps.push_back(c); });
	rep(v,0,n) assert(art[v] == cut[v]);
	for (auto& c : comps) {
		assert(sz(set<int>(all(c))) == sz(c));
		for (int e : c) {
			assert(0 <= e && e < m);
			assert(!bridge[e]);
			seen[e]++;
		}
	}
	rep(e,0,m) assert(seen[e] == !bridge[e]);
}

int main() {
	srand(3);
	rep(it,0,20000) {
		int n = rand() % 18;
		int m = n >= 2 ? rand() % 35 : 0;
		ed.assign(n, {});
		rep(i,0,m) {
			int a = rand() % n, b = rand() % n;
			while (a == b) b = rand() % n;
			ed[a].push_back({b, i});
			ed[b].push_back({a, i});
		}
		testCase();
	}
	cout << "Tests passed!" << endl;
}
