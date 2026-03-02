/**
 * Author: Simon Lindholm
 * Date: 2017-04-17
 * License: CC0
 * Source: folklore
 * Description: Finds all biconnected components in an undirected graph, marks
 *  articulation points in art, and runs a callback for the edges in each.
 *  In a biconnected component there
 *  are at least two internally disjoint paths between any two nodes (a cycle
 *  exists through them). Note that a node can be in several components. An
 *  edge which is not in a component is a bridge, i.e., not part of any cycle.
 * Usage:
 *  int eid = 0; ed.resize(N);
 *  for each edge (a,b) {
 *    ed[a].emplace_back(b, eid);
 *    ed[b].emplace_back(a, eid++); }
 *  bicomps([\&](const vi\& edgelist) {...});
 *  // art[v] = true iff v is an articulation point
 * Time: O(E + V)
 * Status: tested during MIPT ICPC Workshop 2017
 */
#pragma once

vi num, st, art;
vector<vector<pii>> ed;
int Time;
template<class F>
int dfs(int at, int par, F& f) {
	int me = num[at] = ++Time, top = me, ch = 0;
	for (auto [y, e] : ed[at]) if (e != par) {
		if (num[y]) {
			top = min(top, num[y]);
			if (num[y] < me)
				st.push_back(e);
		} else {
			ch++;
			int si = sz(st);
			int up = dfs(y, e, f);
			top = min(top, up);
			if (up >= me && par != -1) art[at] = 1;
			if (up == me) {
				st.push_back(e);
				f(vi(st.begin() + si, st.end()));
				st.resize(si);
			}
			else if (up < me) st.push_back(e);
			else { /* e is a bridge */ }
		}
	}
	if (par == -1 && ch > 1) art[at] = 1;
	return top;
}

template<class F>
void bicomps(F f) {
	num.assign(sz(ed), 0);
	art.assign(sz(ed), 0);
	st.clear();
	Time = 0;
	rep(i,0,sz(ed)) if (!num[i]) dfs(i, -1, f);
}
