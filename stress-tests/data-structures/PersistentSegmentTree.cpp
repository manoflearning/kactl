#include "../utilities/template.h"

#include "../../content/data-structures/PersistentSegmentTree.h"

unsigned X;
int ra() { return int((X = X * 1103515245 + 12345) >> 1); }

ll brute(const vector<ll>& v, int l, int r) {
	ll s = 0;
	rep(i,l,r) s += v[(size_t)i];
	return s;
}

void checkAllRanges(PST& tr, int rt, const vector<ll>& v) {
	int n = sz(v);
	rep(l,0,n+1) rep(r,l,n+1) assert(tr.query(rt, l, r) == brute(v, l, r));
}

int main() {
	{
		PST tr(1);
		int r0 = 0, r1 = tr.add(0, 0, 5), r2 = tr.add(r1, 0, -8);
		assert(tr.query(r0, 0, 1) == 0);
		assert(tr.query(r1, 0, 1) == 5);
		assert(tr.query(r2, 0, 1) == -3);
		assert(tr.query(r2, 0, 0) == 0);
	}

	rep(seed,1,6) {
		X = (unsigned)seed;
		{
			const int N = 7;
			PST tr(N);
			vector<int> roots(1, 0);
			vector<vector<ll>> vals(1, vector<ll>(N));
			rep(it,0,60) {
				int v = ra() % sz(roots), p = ra() % N;
				ll x = ra() % 7 - 3;
				auto old = vals[(size_t)v];
				int oldRoot = roots[(size_t)v];
				int nwRoot = tr.add(oldRoot, p, x);
				old[(size_t)p] += x;
				checkAllRanges(tr, oldRoot, vals[(size_t)v]); // persistence
				checkAllRanges(tr, nwRoot, old);
				roots.push_back(nwRoot);
				vals.push_back(old);
			}
		}

		{
			const int N = 80;
			PST tr(N);
			vector<int> roots(1, 0);
			vector<vector<ll>> vals(1, vector<ll>(N));
			rep(it,0,15000) {
				int v = ra() % sz(roots);
				if (ra() % 5) {
					int l = ra() % (N + 1), r = ra() % (N + 1);
					if (l > r) swap(l, r);
					assert(tr.query(roots[(size_t)v], l, r) == brute(vals[(size_t)v], l, r));
				} else {
					int p = ra() % N;
					ll x = ra() % 2000001 - 1000000;
					roots.push_back(tr.add(roots[(size_t)v], p, x));
					vals.push_back(vals[(size_t)v]);
					vals.back()[(size_t)p] += x;
				}
			}
		}

		{
			const int SIG = 12, N = 32;
			vi a(N);
			rep(i,0,N) a[(size_t)i] = ra() % SIG;
			PST tr(SIG);
			vector<int> root(N + 1);
			root[0] = 0;
			rep(i,0,N) root[(size_t)i + 1] = tr.add(root[(size_t)i], a[(size_t)i], 1);

			rep(l,0,N) {
				vi cnt(SIG);
				rep(r,l+1,N+1) {
					cnt[(size_t)a[(size_t)r - 1]]++;
					int k = 0;
					rep(x,0,SIG) rep(c,0,cnt[(size_t)x]) {
						assert(tr.kth(root[(size_t)l], root[(size_t)r], k++) == x);
					}
				}
			}

			rep(it,0,5000) {
				int l = ra() % (N + 1), r = ra() % (N + 1);
				if (l > r) swap(l, r);
				if (l == r) continue;
				int k = ra() % (r - l);
				int got = tr.kth(root[(size_t)l], root[(size_t)r], k);
				vi b(a.begin() + l, a.begin() + r);
				nth_element(b.begin(), b.begin() + k, b.end());
				assert(got == b[(size_t)k]);
			}
		}
	}

	cout << "Tests passed!" << endl;
}
