#include "../utilities/template.h"

#include "../../content/various/LineHullDP.h"

unsigned X;
int ra() { return int((X = X * 1103515245u + 12345u) >> 1); }

ll brute(const vector<pii>& lines, ll x) {
	ll v = LLONG_MAX;
	for (auto [k, m] : lines) v = min(v, k * x + m);
	return v;
}

void runSeed(unsigned seed) {
	X = seed;
	LineHullDP cht;
	vector<pii> lines;
	ll k = 500, x = -500;
	rep(it,0,20000) {
		if (lines.empty() || ra() % 100 < 55) {
			k -= ra() % 3;
			ll m = ra() % 2000001 - 1000000;
			cht.add(k, m);
			lines.push_back({(int)k, (int)m});
		} else {
			x += ra() % 4;
			assert(cht.query(x) == brute(lines, x));
		}
	}
}

int main() {
	{
		LineHullDP cht;
		cht.add(3, 0);
		cht.add(2, 5);
		cht.add(1, 7);
		rep(x,-10,11) assert(cht.query(x) == min({3LL*x, 2LL*x+5, 1LL*x+7}));
	}
	rep(seed,1,201) runSeed((unsigned)seed);
	cout << "Tests passed!" << endl;
}
